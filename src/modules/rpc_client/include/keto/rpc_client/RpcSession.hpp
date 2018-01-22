/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RpcSession.hpp
 * Author: ubuntu
 *
 * Created on January 22, 2018, 12:32 PM
 */

#ifndef RPCSESSION_HPP
#define RPCSESSION_HPP

#include <memory>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/websocket/ssl.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <string>

#include "keto/rpc_client/Constants.hpp"


using tcp = boost::asio::ip::tcp;               // from <boost/asio/ip/tcp.hpp>
namespace boostSsl = boost::asio::ssl;               // from <boost/asio/ssl.hpp>
namespace websocket = boost::beast::websocket;  // from <boost/beast/websocket.hpp>

namespace keto {
namespace rpc_client {

class RpcSession;

typedef std::shared_ptr<RpcSession> RpcSessionPtr;

class RpcSession : public std::enable_shared_from_this<RpcSession> {
public:
    RpcSession(std::shared_ptr<boost::asio::io_context> ioc, 
            std::shared_ptr<boostSsl::context> ctx,
            const std::string& host);
    RpcSession(const RpcSession& orig) = delete;
    virtual ~RpcSession();
    
    void run();
    void on_resolve(
        boost::system::error_code ec,
        tcp::resolver::results_type results);
    void
    on_connect(boost::system::error_code ec);
    
    void
    on_ssl_handshake(boost::system::error_code ec);
    
    void
    on_handshake(boost::system::error_code ec);

    
    void
    on_write(boost::system::error_code ec,
            std::size_t bytes_transferred);
    
    void
    on_read(
            boost::system::error_code ec,
            std::size_t bytes_transferred);
    
    void
    on_close(boost::system::error_code ec);
private:
    tcp::resolver resolver;
    websocket::stream<boostSsl::stream<tcp::socket>> ws_;
    boost::beast::multi_buffer buffer_;
    std::string host;
    std::string port;
};


}
}

#endif /* RPCSESSION_HPP */

