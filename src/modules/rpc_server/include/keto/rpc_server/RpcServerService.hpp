/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RpcServerService.hpp
 * Author: ubuntu
 *
 * Created on March 31, 2018, 10:08 AM
 */

#ifndef RPCSERVERSERVICE_HPP
#define RPCSERVERSERVICE_HPP

#include <string>
#include <memory>

namespace keto {
namespace rpc_server {

class RpcServerService;
typedef std::shared_ptr<RpcServerService> RpcServerServicePtr;

class RpcServerService {
public:
    RpcServerService();
    RpcServerService(const RpcServerService& orig) = delete;
    virtual ~RpcServerService();
    
    static RpcServerServicePtr init();
    static void fin();
    static RpcServerServicePtr getInstance();

    keto::event::Event sendMessage(const keto::event::Event& event);
private:

};


}
}

#endif /* RPCSERVERSERVICE_HPP */

