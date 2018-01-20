/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RpcServerModule.hpp
 * Author: brett chaldecott
 *
 * Created on January 20, 2018, 2:46 PM
 */

#ifndef RPCSERVERMODULE_HPP
#define RPCSERVERMODULE_HPP

#include <string>
#include <map>
#include <memory>

#include "keto/module/ModuleInterface.hpp"

namespace keto {
namespace rpc_server {

class RpcServerModule : public keto::module::ModuleInterface {
public:
    RpcServerModule();
    RpcServerModule(const RpcServerModule& orig) = delete;
    virtual ~RpcServerModule();
    
    // meta methods
    virtual const std::string getName() const;
    virtual const std::string getDescription() const;
    virtual const std::string getVersion() const;

private:

};


}
}

#endif /* RPCSERVERMODULE_HPP */

