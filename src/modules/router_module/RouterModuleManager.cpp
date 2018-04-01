/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RouterModuleManager.cpp
 * Author: ubuntu
 * 
 * Created on February 9, 2018, 11:12 AM
 */

#include <boost/dll/alias.hpp>
#include <boost/dll/shared_library.hpp>
#include <boost/shared_ptr.hpp>

#include "keto/common/Log.hpp"
#include "keto/common/MetaInfo.hpp"
#include "keto/router/RouterModuleManager.hpp"
#include "keto/router/RouterService.hpp"
#include "keto/router/RouterRegistry.hpp"
#include "keto/router/EventRegistry.hpp"
#include "keto/router/StorageManager.hpp"
#include "include/keto/router/RouterRegistry.hpp"

namespace keto {
namespace router {


RouterModuleManager::RouterModuleManager() {
}


RouterModuleManager::~RouterModuleManager() {
}

// meta methods
const std::string RouterModuleManager::getName() const {
    return "RouterModuleManager";
}


const std::string RouterModuleManager::getDescription() const {
    return "The router module manager responsible for managing the routes.";
}


const std::string RouterModuleManager::getVersion() const {
    return keto::common::MetaInfo::VERSION;
}

// lifecycle methods
void RouterModuleManager::start() {
    RouterRegistry::init();
    StorageManager::init();
    RouterService::init();
    modules["routerModule"] = std::make_shared<RouterModule>();
    EventRegistry::registerEventHandlers();
    KETO_LOG_INFO << "[RouterModuleManager] Started the RouterModuleManager";
}


void RouterModuleManager::stop() {
    EventRegistry::deregisterEventHandlers();
    modules.clear();
    RouterService::fin();
    StorageManager::fin();
    RouterRegistry::fin();
    KETO_LOG_INFO << "[RouterModuleManager] The RouterModuleManager is being stopped";
}


const std::vector<std::string> RouterModuleManager::listModules() {
    std::vector<std::string> keys;
    std::transform(
        this->modules.begin(),
        this->modules.end(),
        std::back_inserter(keys),
        [](const std::map<std::string,std::shared_ptr<keto::module::ModuleInterface>>::value_type 
            &pair){return pair.first;});
    return keys;
}

const std::shared_ptr<keto::module::ModuleInterface> RouterModuleManager::getModule(const std::string& name) {
    return modules[name];
}


boost::shared_ptr<RouterModuleManager> RouterModuleManager::create_module() {
    return boost::shared_ptr<RouterModuleManager>(new RouterModuleManager());    
}

BOOST_DLL_ALIAS(
    keto::router::RouterModuleManager::create_module,
    create_module
)


}
}