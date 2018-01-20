/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RpcServerModuleManager.cpp
 * Author: ubuntu
 * 
 * Created on January 20, 2018, 2:42 PM
 */

#include <boost/dll/alias.hpp>
#include <boost/dll/shared_library.hpp>
#include <boost/shared_ptr.hpp>

#include "keto/common/Log.hpp"

#include "keto/rpc_server/RpcServerModuleManager.hpp"

namespace keto {
namespace rpc_server {

RpcServerModuleManager::RpcServerModuleManager() {
}

RpcServerModuleManager::~RpcServerModuleManager() {
}

// meta methods
const std::string RpcServerModuleManager::getName() const {
    return "RpcServerModuleManager";
}

const std::string RpcServerModuleManager::getDescription() const {
    return "The rpc server module manager responsible for managing inbound connections";
}

const std::string RpcServerModuleManager::getVersion() const {
    return "0.1.0";
}

// lifecycle methods
void RpcServerModuleManager::start() {
    modules["RpcServerModuleManager"] = std::make_shared<RpcServerModule>();
    KETO_LOG_INFO << "[RpcServerModuleManager] Started the RpcServerModuleManager";
}

void RpcServerModuleManager::stop() {
    modules.clear();
    KETO_LOG_INFO << "[RpcServerModuleManager] The RpcServerModuleManager is being stopped";

}

const std::vector<std::string> RpcServerModuleManager::listModules() {
    std::vector<std::string> keys;
    std::transform(
        this->modules.begin(),
        this->modules.end(),
        std::back_inserter(keys),
        [](const std::map<std::string,std::shared_ptr<keto::module::ModuleInterface>>::value_type 
            &pair){return pair.first;});
    return keys;
}

const std::shared_ptr<keto::module::ModuleInterface> RpcServerModuleManager::getModule(const std::string& name) {
    return modules[name];
}

boost::shared_ptr<RpcServerModuleManager> RpcServerModuleManager::create_module() {
    return boost::shared_ptr<RpcServerModuleManager>(new RpcServerModuleManager());
}

BOOST_DLL_ALIAS(
    keto::rpc_server::RpcServerModuleManager::create_module,
    create_module                               
)


}
}