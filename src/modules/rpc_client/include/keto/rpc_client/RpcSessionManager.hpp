/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RpcSessionManager.hpp
 * Author: ubuntu
 *
 * Created on January 22, 2018, 1:18 PM
 */

#ifndef RPCSESSIONMANAGER_HPP
#define RPCSESSIONMANAGER_HPP

#include "keto/rpc_client/RpcSession.hpp"

#include <thread>
#include <vector>

namespace keto {
namespace rpc_client {

class RpcSessionManager;
typedef std::shared_ptr<RpcSessionManager> RpcSessionManagerPtr;

class RpcSessionManager {
public:
    RpcSessionManager();
    RpcSessionManager(const RpcSessionManager& orig) = delete;
    virtual ~RpcSessionManager();
    
    std::vector<std::string> listPeers();
    
    void start();
    void stop();
    
private:
    std::map<std::string,RpcSessionPtr> sessionMap;
    // The io_context is required for all I/O
    std::shared_ptr<boost::asio::io_context> ioc;
    // The SSL context is required, and holds certificates
    std::shared_ptr<boostSsl::context> ctx;
    // the thread information
    int threads;
    std::vector<std::thread> threadsVector;
    
};


}
}

#endif /* RPCSESSIONMANAGER_HPP */

