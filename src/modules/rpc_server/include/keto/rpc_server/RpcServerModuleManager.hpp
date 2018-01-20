/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RpcServerModuleManager.hpp
 * Author: ubuntu
 *
 * Created on January 20, 2018, 2:42 PM
 */

#ifndef RPCSERVERMODULEMANAGER_HPP
#define RPCSERVERMODULEMANAGER_HPP

#include <string>
#include <map>
#include <memory>

#include "keto/module/ModuleManagementInterface.hpp"
#include "keto/rpc_server/RpcServerModule.hpp"

namespace keto {
namespace rpc_server {

class RpcServerModuleManager : public keto::module::ModuleManagementInterface {
public:
    RpcServerModuleManager();
    RpcServerModuleManager(const RpcServerModuleManager& orig) = delete;
    virtual ~RpcServerModuleManager();
    
    // meta methods
    virtual const std::string getName() const;
    virtual const std::string getDescription() const;
    virtual const std::string getVersion() const;
    
    // lifecycle methods
    virtual void start();
    virtual void stop();
    
    virtual const std::vector<std::string> listModules();
    virtual const std::shared_ptr<keto::module::ModuleInterface> getModule(const std::string& name);
    
    static boost::shared_ptr<RpcServerModuleManager> create_module();

private:
    std::map<std::string,std::shared_ptr<keto::module::ModuleInterface>> modules;
};

}
}

#endif /* RPCSERVERMODULEMANAGER_HPP */

