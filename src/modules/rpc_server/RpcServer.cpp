/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RpcServer.cpp
 * Author: ubuntu
 * 
 * Created on January 22, 2018, 7:08 AM
 */


#include "keto/rpc_server/RpcServer.hpp"
#include "keto/rpc_server/Constants.hpp"
#include "keto/ssl/ServerCertificate.hpp"
#include "keto/environment/EnvironmentManager.hpp"

using tcp = boost::asio::ip::tcp;               // from <boost/asio/ip/tcp.hpp>
namespace beastSsl = boost::asio::ssl;               // from <boost/asio/ssl.hpp>
namespace websocket = boost::beast::websocket;  // from <boost/beast/websocket.hpp>

namespace keto {
namespace rpc_server {

// Report a failure
void
fail(boost::system::error_code ec, char const* what)
{
    std::cerr << what << ": " << ec.message() << "\n";
}

// Echoes back all received WebSocket messages
class session : public std::enable_shared_from_this<session>
{
    tcp::socket socket_;
    websocket::stream<beastSsl::stream<tcp::socket&>> ws_;
    boost::asio::strand<
        boost::asio::io_context::executor_type> strand_;
    boost::beast::multi_buffer buffer_;

public:
    // Take ownership of the socket
    session(tcp::socket socket, beastSsl::context& ctx)
        : socket_(std::move(socket))
        , ws_(socket_, ctx)
        , strand_(ws_.get_executor())
    {
    }

    // Start the asynchronous operation
    void
    run()
    {
        // Perform the SSL handshake
        ws_.next_layer().async_handshake(
            beastSsl::stream_base::server,
            boost::asio::bind_executor(
                strand_,
                std::bind(
                    &session::on_handshake,
                    shared_from_this(),
                    std::placeholders::_1)));
    }

    void
    on_handshake(boost::system::error_code ec)
    {
        if(ec)
            return fail(ec, "handshake");

        // Accept the websocket handshake
        ws_.async_accept(
            boost::asio::bind_executor(
                strand_,
                std::bind(
                    &session::on_accept,
                    shared_from_this(),
                    std::placeholders::_1)));
    }

    void
    on_accept(boost::system::error_code ec)
    {
        if(ec)
            return fail(ec, "accept");

        // Read a message
        do_read();
    }

    void
    do_read()
    {
        // Read a message into our buffer
        ws_.async_read(
            buffer_,
            boost::asio::bind_executor(
                strand_,
                std::bind(
                    &session::on_read,
                    shared_from_this(),
                    std::placeholders::_1,
                    std::placeholders::_2)));
    }

    void
    on_read(
        boost::system::error_code ec,
        std::size_t bytes_transferred)
    {
        boost::ignore_unused(bytes_transferred);

        // This indicates that the session was closed
        if(ec == websocket::error::closed)
            return;

        if(ec)
            fail(ec, "read");

        // Echo the message
        ws_.text(ws_.got_text());
        ws_.async_write(
            buffer_.data(),
            boost::asio::bind_executor(
                strand_,
                std::bind(
                    &session::on_write,
                    shared_from_this(),
                    std::placeholders::_1,
                    std::placeholders::_2)));
    }

    void
    on_write(
        boost::system::error_code ec,
        std::size_t bytes_transferred)
    {
        boost::ignore_unused(bytes_transferred);

        if(ec)
            return fail(ec, "write");

        // Clear the buffer
        buffer_.consume(buffer_.size());

        // Do another read
        do_read();
    }
};

//------------------------------------------------------------------------------

// Accepts incoming connections and launches the sessions
class listener : public std::enable_shared_from_this<listener>
{
    std::shared_ptr<beastSsl::context> ctx_;
    tcp::acceptor acceptor_;
    tcp::socket socket_;

public:
    listener(
        std::shared_ptr<boost::asio::io_context> ioc,
        std::shared_ptr<beastSsl::context> ctx,
        tcp::endpoint endpoint)
        : ctx_(ctx)
        , acceptor_(*ioc)
        , socket_(*ioc)
    {
        boost::system::error_code ec;

        // Open the acceptor
        acceptor_.open(endpoint.protocol(), ec);
        if(ec)
        {
            fail(ec, "open");
            return;
        }
        
        // this solves the shut down problem
        acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
        
        // Bind to the server address
        acceptor_.bind(endpoint, ec);
        if(ec)
        {
            fail(ec, "bind");
            return;
        }

        // Start listening for connections
        acceptor_.listen(
            boost::asio::socket_base::max_listen_connections, ec);
        if(ec)
        {
            fail(ec, "listen");
            return;
        }
    }

    // Start accepting incoming connections
    void
    run()
    {
        if(! acceptor_.is_open())
            return;
        do_accept();
    }

    void
    do_accept()
    {
        acceptor_.async_accept(
            socket_,
            std::bind(
                &listener::on_accept,
                shared_from_this(),
                std::placeholders::_1));
    }

    void
    on_accept(boost::system::error_code ec)
    {
        if(ec)
        {
            fail(ec, "accept");
        }
        else
        {
            // Create the session and run it
            std::make_shared<session>(std::move(socket_), *ctx_)->run();
        }

        // Accept another connection
        do_accept();
    }
};

std::shared_ptr<listener> listenerPtr;

namespace ketoEnv = keto::environment;

RpcServer::RpcServer() {
    // retrieve the configuration
    std::shared_ptr<ketoEnv::Config> config = ketoEnv::EnvironmentManager::getInstance()->getConfig();
    
    serverIp = boost::asio::ip::make_address(Constants::DEFAULT_IP);
    if (config->getVariablesMap().count(Constants::IP_ADDRESS)) {
        serverIp = boost::asio::ip::make_address(
                config->getVariablesMap()[Constants::IP_ADDRESS].as<std::string>());
    }
    
    serverPort = Constants::DEFAULT_PORT_NUMBER;
    if (config->getVariablesMap().count(Constants::PORT_NUMBER)) {
        serverPort = static_cast<unsigned short>(
                atoi(config->getVariablesMap()[Constants::PORT_NUMBER].as<std::string>().c_str()));
    }
    
    threads = Constants::DEFAULT_HTTP_THREADS;
    if (config->getVariablesMap().count(Constants::HTTP_THREADS)) {
        threads = std::max<int>(1,atoi(config->getVariablesMap()[Constants::HTTP_THREADS].as<std::string>().c_str()));
    }
    
}

RpcServer::~RpcServer() {
}

void RpcServer::start() {
    // The io_context is required for all I/O
    this->ioc = std::make_shared<boost::asio::io_context>(this->threads);

    // The SSL context is required, and holds certificates
    this->contextPtr = std::make_shared<beastSsl::context>(beastSsl::context::sslv23);

    // This holds the self-signed certificate used by the server
    load_server_certificate(*(this->contextPtr));
    
    // Create and launch a listening port
    listenerPtr = std::make_shared<listener>(ioc,
        contextPtr,
        tcp::endpoint{this->serverIp, this->serverPort});
    listenerPtr->run();
    
    // Run the I/O service on the requested number of threads
    this->threadsVector.reserve(this->threads);
    for(int i = 0; i < this->threads; i++) {
        this->threadsVector.emplace_back(
        [this]
        {
            this->ioc->run();
        });
    }
}
    
void RpcServer::stop() {
    this->ioc->stop();
    
    for (std::vector<std::thread>::iterator iter = this->threadsVector.begin();
            iter != this->threadsVector.end(); iter++) {
        iter->join();
    }

    listenerPtr.reset();
    
    this->threadsVector.clear();
}
    


}
}