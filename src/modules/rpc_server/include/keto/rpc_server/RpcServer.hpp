/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RpcServer.hpp
 * Author: ubuntu
 *
 * Created on January 22, 2018, 7:08 AM
 */

#ifndef RPCSERVER_HPP
#define RPCSERVER_HPP

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/websocket/ssl.hpp>
#include <boost/asio/bind_executor.hpp>
#include <boost/asio/strand.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>

using tcp = boost::asio::ip::tcp;               // from <boost/asio/ip/tcp.hpp>
namespace beastSsl = boost::asio::ssl;               // from <boost/asio/ssl.hpp>
namespace websocket = boost::beast::websocket;  // from <boost/beast/websocket.hpp>


namespace keto {
namespace rpc_server {

class RpcServer;
typedef std::shared_ptr<RpcServer> RpcServerPtr;
    
class RpcServer {
public:
    RpcServer();
    RpcServer(const RpcServer& orig) = delete;
    virtual ~RpcServer();
    
    void start();
    
    void stop();
    
    
private:
    boost::asio::ip::address serverIp;
    unsigned short serverPort;
    int threads;
    std::shared_ptr<beastSsl::context> contextPtr;
    std::shared_ptr<boost::asio::io_context> ioc;
    std::vector<std::thread> threadsVector;
    
};

}
}

#endif /* RPCSERVER_HPP */

