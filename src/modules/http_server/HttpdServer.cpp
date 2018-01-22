/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HttpdServer.cpp
 * Author: ubuntu
 * 
 * Created on January 21, 2018, 5:10 AM
 */

#include <chrono>
#include <thread>

#include "keto/http/HttpdServer.hpp"
#include "keto/http/Constants.hpp"
#include "keto/ssl/ServerCertificate.hpp"
#include "keto/environment/EnvironmentManager.hpp"




namespace keto {
namespace http {

//
// Copyright (c) 2016-2017 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

//------------------------------------------------------------------------------
//
// Example: HTTP SSL server, asynchronous
//
//------------------------------------------------------------------------------


// Return a reasonable mime type based on the extension of a file.
boost::beast::string_view
mime_type(boost::beast::string_view path)
{
    using boost::beast::iequals;
    auto const ext = [&path]
    {
        auto const pos = path.rfind(".");
        if(pos == boost::beast::string_view::npos)
            return boost::beast::string_view{};
        return path.substr(pos);
    }();
    if(iequals(ext, ".htm"))  return "text/html";
    if(iequals(ext, ".html")) return "text/html";
    if(iequals(ext, ".php"))  return "text/html";
    if(iequals(ext, ".css"))  return "text/css";
    if(iequals(ext, ".txt"))  return "text/plain";
    if(iequals(ext, ".js"))   return "application/javascript";
    if(iequals(ext, ".json")) return "application/json";
    if(iequals(ext, ".xml"))  return "application/xml";
    if(iequals(ext, ".swf"))  return "application/x-shockwave-flash";
    if(iequals(ext, ".flv"))  return "video/x-flv";
    if(iequals(ext, ".png"))  return "image/png";
    if(iequals(ext, ".jpe"))  return "image/jpeg";
    if(iequals(ext, ".jpeg")) return "image/jpeg";
    if(iequals(ext, ".jpg"))  return "image/jpeg";
    if(iequals(ext, ".gif"))  return "image/gif";
    if(iequals(ext, ".bmp"))  return "image/bmp";
    if(iequals(ext, ".ico"))  return "image/vnd.microsoft.icon";
    if(iequals(ext, ".tiff")) return "image/tiff";
    if(iequals(ext, ".tif"))  return "image/tiff";
    if(iequals(ext, ".svg"))  return "image/svg+xml";
    if(iequals(ext, ".svgz")) return "image/svg+xml";
    return "application/text";
}

// Append an HTTP rel-path to a local filesystem path.
// The returned path is normalized for the platform.
std::string
path_cat(
    boost::beast::string_view base,
    boost::beast::string_view path)
{
    if(base.empty())
        return path.to_string();
    std::string result = base.to_string();
#if BOOST_MSVC
    char constexpr path_separator = '\\';
    if(result.back() == path_separator)
        result.resize(result.size() - 1);
    result.append(path.data(), path.size());
    for(auto& c : result)
        if(c == '/')
            c = path_separator;
#else
    char constexpr path_separator = '/';
    if(result.back() == path_separator)
        result.resize(result.size() - 1);
    result.append(path.data(), path.size());
#endif
    return result;
}

// This function produces an HTTP response for the given
// request. The type of the response object depends on the
// contents of the request, so the interface requires the
// caller to pass a generic lambda for receiving the response.
template<
    class Body, class Allocator,
    class Send>
void
handle_request(
    boost::beast::string_view doc_root,
    httpBeast::request<Body, httpBeast::basic_fields<Allocator>>&& req,
    Send&& send)
{
    // Returns a bad request response
    auto const bad_request =
    [&req](boost::beast::string_view why)
    {
        httpBeast::response<httpBeast::string_body> res{httpBeast::status::bad_request, req.version()};
        res.set(httpBeast::field::server, BOOST_BEAST_VERSION_STRING);
        res.set(httpBeast::field::content_type, "text/html");
        res.keep_alive(req.keep_alive());
        res.body() = why.to_string();
        res.prepare_payload();
        return res;
    };

    // Returns a not found response
    auto const not_found =
    [&req](boost::beast::string_view target)
    {
        httpBeast::response<httpBeast::string_body> res{httpBeast::status::not_found, req.version()};
        res.set(httpBeast::field::server, BOOST_BEAST_VERSION_STRING);
        res.set(httpBeast::field::content_type, "text/html");
        res.keep_alive(req.keep_alive());
        res.body() = "The resource '" + target.to_string() + "' was not found.";
        res.prepare_payload();
        return res;
    };

    // Returns a server error response
    auto const server_error =
    [&req](boost::beast::string_view what)
    {
        httpBeast::response<httpBeast::string_body> res{httpBeast::status::internal_server_error, req.version()};
        res.set(httpBeast::field::server, BOOST_BEAST_VERSION_STRING);
        res.set(httpBeast::field::content_type, "text/html");
        res.keep_alive(req.keep_alive());
        res.body() = "An error occurred: '" + what.to_string() + "'";
        res.prepare_payload();
        return res;
    };

    // Make sure we can handle the method
    if( req.method() != httpBeast::verb::get &&
        req.method() != httpBeast::verb::head)
        return send(bad_request("Unknown HTTP-method"));

    // Request path must be absolute and not contain "..".
    if( req.target().empty() ||
        req.target()[0] != '/' ||
        req.target().find("..") != boost::beast::string_view::npos)
        return send(bad_request("Illegal request-target"));

    // Build the path to the requested file
    
    std::string path = path_cat(doc_root, req.target());
    if(req.target().back() == '/')
        path.append("index.html");

    // Attempt to open the file
    boost::beast::error_code ec;
    httpBeast::file_body::value_type body;
    body.open(path.c_str(), boost::beast::file_mode::scan, ec);

    // Handle the case where the file doesn't exist
    if(ec == boost::system::errc::no_such_file_or_directory)
        return send(not_found(req.target()));

    // Handle an unknown error
    if(ec)
        return send(server_error(ec.message()));

    // Respond to HEAD request
    if(req.method() == httpBeast::verb::head)
    {
        httpBeast::response<httpBeast::empty_body> res{httpBeast::status::ok, req.version()};
        res.set(httpBeast::field::server, BOOST_BEAST_VERSION_STRING);
        res.set(httpBeast::field::content_type, mime_type(path));
        res.content_length(body.size());
        res.keep_alive(req.keep_alive());
        return send(std::move(res));
    }

    // Respond to GET request
    httpBeast::response<httpBeast::file_body> res{
        std::piecewise_construct,
        std::make_tuple(std::move(body)),
        std::make_tuple(httpBeast::status::ok, req.version())};
    res.set(httpBeast::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(httpBeast::field::content_type, mime_type(path));
    res.content_length(body.size());
    res.keep_alive(req.keep_alive());
    return send(std::move(res));
}

//------------------------------------------------------------------------------

// Report a failure
void
fail(boost::system::error_code ec, char const* what)
{
    std::cerr << what << ": " << ec.message() << "\n";
}

// Handles an HTTP server connection
class session : public std::enable_shared_from_this<session>
{
    // This is the C++11 equivalent of a generic lambda.
    // The function object is used to send an HTTP message.
    struct send_lambda
    {
        session& self_;

        explicit
        send_lambda(session& self)
            : self_(self)
        {
        }

        template<bool isRequest, class Body, class Fields>
        void
        operator()(httpBeast::message<isRequest, Body, Fields>&& msg) const
        {
            // The lifetime of the message has to extend
            // for the duration of the async operation so
            // we use a shared_ptr to manage it.
            auto sp = std::make_shared<
                httpBeast::message<isRequest, Body, Fields>>(std::move(msg));

            // Store a type-erased version of the shared
            // pointer in the class to keep it alive.
            self_.res_ = sp;

            // Write the response
            httpBeast::async_write(
                self_.stream_,
                *sp,
                boost::asio::bind_executor(
                    self_.strand_,
                    std::bind(
                        &session::on_write,
                        self_.shared_from_this(),
                        std::placeholders::_1,
                        std::placeholders::_2,
                        sp->need_eof())));
        }
    };

    tcp::socket socket_;
    ssl::stream<tcp::socket&> stream_;
    boost::asio::strand<
        boost::asio::io_context::executor_type> strand_;
    boost::beast::flat_buffer buffer_;
    std::string const& doc_root_;
    httpBeast::request<httpBeast::string_body> req_;
    std::shared_ptr<void> res_;
    send_lambda lambda_;

public:
    // Take ownership of the socket
    explicit
    session(
        tcp::socket socket,
        ssl::context& ctx,
        std::string const& doc_root)
        : socket_(std::move(socket))
        , stream_(socket_, ctx)
        , strand_(socket_.get_executor())
        , doc_root_(doc_root)
        , lambda_(*this)
    {
    }

    // Start the asynchronous operation
    void
    run()
    {
        // Perform the SSL handshake
        stream_.async_handshake(
            ssl::stream_base::server,
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

        do_read();
    }

    void
    do_read()
    {
        // Read a request
        httpBeast::async_read(stream_, buffer_, req_,
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

        // This means they closed the connection
        if(ec == httpBeast::error::end_of_stream)
            return do_close();

        if(ec)
            return fail(ec, "read");

        // Send the response
        handle_request(doc_root_, std::move(req_), lambda_);
    }

    void
    on_write(
        boost::system::error_code ec,
        std::size_t bytes_transferred,
        bool close)
    {
        boost::ignore_unused(bytes_transferred);

        if(ec)
            return fail(ec, "write");

        if(close)
        {
            // This means we should close the connection, usually because
            // the response indicated the "Connection: close" semantic.
            return do_close();
        }

        // We're done with the response so delete it
        res_ = nullptr;

        // Read another request
        do_read();
    }

    void
    do_close()
    {
        // Perform the SSL shutdown
        stream_.async_shutdown(
            boost::asio::bind_executor(
                strand_,
                std::bind(
                    &session::on_shutdown,
                    shared_from_this(),
                    std::placeholders::_1)));
    }

    void
    on_shutdown(boost::system::error_code ec)
    {
        if(ec)
            return fail(ec, "shutdown");

        // At this point the connection is closed gracefully
    }
};

//------------------------------------------------------------------------------

// Accepts incoming connections and launches the sessions
class listener : public std::enable_shared_from_this<listener>
{
    std::shared_ptr<ssl::context> ctx_;
    tcp::acceptor acceptor_;
    tcp::socket socket_;
    std::string const& doc_root_;

public:
    listener(
        std::shared_ptr<boost::asio::io_context> ioc,
        std::shared_ptr<ssl::context> ctx,
        tcp::endpoint endpoint,
         const std::string& doc_root)
        : ctx_(ctx)
        , acceptor_(*ioc)
        , socket_(*ioc)
        , doc_root_(doc_root)
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
            // backoff to prevent the cpu from using all available resources
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        else
        {
            // Create the session and run it
            std::shared_ptr<session> sessionPtr = std::make_shared<session>(
                std::move(socket_),
                *ctx_,
                doc_root_);
            sessionPtr->run();
        }

        // Accept another connection
        do_accept();
    }
};

std::shared_ptr<listener> listenerPtr;

namespace ketoEnv = keto::environment;

HttpdServer::HttpdServer() {
    // retrieve the configuration
    std::shared_ptr<ketoEnv::Config> config = ketoEnv::EnvironmentManager::getInstance()->getConfig();
    
    // retrieve the path
    documentRoot = (ketoEnv::EnvironmentManager::getInstance()->getEnv()->getInstallDir() /
            Constants::DOCUMENT_ROOT_DEFAULT);
    if (config->getVariablesMap().count(Constants::DOCUMENT_ROOT)) {
        documentRoot = config->getVariablesMap()[Constants::DOCUMENT_ROOT].as<std::string>();
    }
    
    // retrieve the path
    documentRoot = (ketoEnv::EnvironmentManager::getInstance()->getEnv()->getInstallDir() /
            Constants::DOCUMENT_ROOT_DEFAULT);
    if (config->getVariablesMap().count(Constants::DOCUMENT_ROOT)) {
        documentRoot = config->getVariablesMap()[Constants::DOCUMENT_ROOT].as<std::string>();
    }
    
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

HttpdServer::~HttpdServer() {
}

void HttpdServer::start() {
    // The io_context is required for all I/O
    this->ioc = std::make_shared<boost::asio::io_context>(this->threads);

    // The SSL context is required, and holds certificates
    this->contextPtr = std::make_shared<ssl::context>(ssl::context::sslv23);

    // This holds the self-signed certificate used by the server
    load_server_certificate(*(this->contextPtr));

    // Create and launch a listening port
    listenerPtr = std::make_shared<listener>(
        ioc,
        contextPtr,
        tcp::endpoint{this->serverIp, this->serverPort},
        documentRoot.string());
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

void HttpdServer::stop() {
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