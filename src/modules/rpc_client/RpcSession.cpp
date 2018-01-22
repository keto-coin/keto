/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RpcSession.cpp
 * Author: ubuntu
 * 
 * Created on January 22, 2018, 12:32 PM
 */


#include <string>

#include "keto/ssl/RootCertificate.hpp"
#include "keto/rpc_client/RpcSession.hpp"
#include "include/keto/rpc_client/RpcSession.hpp"
#include <boost/algorithm/string.hpp>


namespace keto {
namespace rpc_client {

// Report a failure
void
fail(boost::system::error_code ec, char const* what)
{
    std::cerr << what << ": " << ec.message() << "\n";
}

RpcSession::RpcSession(std::shared_ptr<boost::asio::io_context> ioc, 
    std::shared_ptr<boostSsl::context> ctx, const std::string& host) :
        resolver(*ioc),
        ws_(*ioc, *ctx),
        host(host) {
    if (host.find(":") != std::string::npos) {
        std::vector<std::string> results;
        boost::split(results, host, [](char c){return c == ':';});
        this->host = results[0];
        this->port = results[1];
    } else {
        this->port = Constants::DEFAULT_PORT_NUMBER;
    }
    
}

RpcSession::~RpcSession() {
}

// Start the asynchronous operation
void
RpcSession::run()
{
    // Look up the domain name
    this->resolver.async_resolve(
        host.c_str(),
        port.c_str(),
        std::bind(
            &RpcSession::on_resolve,
            shared_from_this(),
            std::placeholders::_1,
            std::placeholders::_2));
}

void
RpcSession::on_resolve(
    boost::system::error_code ec,
    tcp::resolver::results_type results)
{
    if(ec)
        return fail(ec, "resolve");

    // Make the connection on the IP address we get from a lookup
    boost::asio::async_connect(
        ws_.next_layer().next_layer(),
        results.begin(),
        results.end(),
        std::bind(
            &RpcSession::on_connect,
            shared_from_this(),
            std::placeholders::_1));
}

void
RpcSession::on_connect(boost::system::error_code ec)
{
    if(ec)
        return fail(ec, "connect");

    // Perform the SSL handshake
    ws_.next_layer().async_handshake(
        boostSsl::stream_base::client,
        std::bind(
            &RpcSession::on_ssl_handshake,
            shared_from_this(),
            std::placeholders::_1));
}

void
RpcSession::on_ssl_handshake(boost::system::error_code ec)
{
    if(ec)
        return fail(ec, "ssl_handshake");

    // Perform the websocket handshake
    ws_.async_handshake(host, "/",
        std::bind(
            &RpcSession::on_handshake,
            shared_from_this(),
            std::placeholders::_1));
}

void
RpcSession::on_handshake(boost::system::error_code ec)
{
    if(ec)
        return fail(ec, "handshake");

    // Send the message
    ws_.async_write(
        boost::asio::buffer(std::string(Constants::PEER_HELLO)),
        std::bind(
            &RpcSession::on_write,
            shared_from_this(),
            std::placeholders::_1,
            std::placeholders::_2));
}


void
RpcSession::on_write(
    boost::system::error_code ec,
    std::size_t bytes_transferred)
{
    boost::ignore_unused(bytes_transferred);

    if(ec)
        return fail(ec, "write");

    // Read a message into our buffer
    ws_.async_read(
        buffer_,
        std::bind(
            &RpcSession::on_read,
            shared_from_this(),
            std::placeholders::_1,
            std::placeholders::_2));
}

void
RpcSession::on_read(
    boost::system::error_code ec,
    std::size_t bytes_transferred)
{
    boost::ignore_unused(bytes_transferred);

    if(ec)
        return fail(ec, "read");

    // Close the WebSocket connection
    ws_.async_close(websocket::close_code::normal,
        std::bind(
            &RpcSession::on_close,
            shared_from_this(),
            std::placeholders::_1));
}

void
RpcSession::on_close(boost::system::error_code ec)
{
    if(ec)
        return fail(ec, "close");

    // If we get here then the connection is closed gracefully

    // The buffers() function helps print a ConstBufferSequence
    std::cout << boost::beast::buffers(buffer_.data()) << std::endl;
}


}
}