/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SandboxModuleManager.cpp
 * Author: brett chaldecott
 * 
 * Created on January 20, 2018, 4:25 PM
 */

#include <boost/dll/alias.hpp>
#include <boost/dll/shared_library.hpp>
#include <boost/shared_ptr.hpp>

#include "keto/common/Log.hpp"
#include "keto/common/MetaInfo.hpp"

#include "keto/sandbox/SandboxModuleManager.hpp"
#include "keto/sandbox/SandboxService.hpp"
#include "keto/sandbox/EventRegistry.hpp"
#include "keto/server_common/ServiceRegistryHelper.hpp"
#include "keto/server_common/Constants.hpp"
#include "keto/wavm_common/WavmEngineManager.hpp"



namespace keto {
namespace sandbox {

SandboxModuleManager::SandboxModuleManager() {
}

SandboxModuleManager::~SandboxModuleManager() {
}

// meta methods
const std::string SandboxModuleManager::getName() const {
    return "SandboxModuleManager";
}

const std::string SandboxModuleManager::getDescription() const {
    return "The sandbox module manager responsible for managing the sandbox processing area.";
}

const std::string SandboxModuleManager::getVersion() const {
    return keto::common::MetaInfo::VERSION;
}

// lifecycle methods
void SandboxModuleManager::start() {
    modules["SandboxModule"] = std::make_shared<SandboxModule>();
    keto::wavm_common::WavmEngineManager::init();
    SandboxService::init();
    EventRegistry::registerEventHandlers();
    KETO_LOG_INFO << "[SandboxModuleManager] Started the SandboxModuleManager";
}

void SandboxModuleManager::stop() {
    EventRegistry::deregisterEventHandlers();
    SandboxService::fin();
    keto::wavm_common::WavmEngineManager::fin();
    modules.clear();
    KETO_LOG_INFO << "[SandboxModuleManager] The SandboxModuleManager is being stopped";

}

void SandboxModuleManager::postStart() {
    KETO_LOG_INFO << "[SandboxModuleManager] The post start method has been called";
    keto::server_common::registerService(keto::server_common::Constants::SERVICE::PROCESS);
    KETO_LOG_INFO << "[SandboxModuleManager] The post start method is complete";
}

const std::vector<std::string> SandboxModuleManager::listModules() {
    std::vector<std::string> keys;
    std::transform(
        this->modules.begin(),
        this->modules.end(),
        std::back_inserter(keys),
        [](const std::map<std::string,std::shared_ptr<keto::module::ModuleInterface>>::value_type 
            &pair){return pair.first;});
    return keys;
}

const std::shared_ptr<keto::module::ModuleInterface> SandboxModuleManager::getModule(const std::string& name) {
    return modules[name];
}

boost::shared_ptr<SandboxModuleManager> SandboxModuleManager::create_module() {
    return boost::shared_ptr<SandboxModuleManager>(new SandboxModuleManager());
}

BOOST_DLL_ALIAS(
    keto::sandbox::SandboxModuleManager::create_module,
    create_module                               
)


}
}