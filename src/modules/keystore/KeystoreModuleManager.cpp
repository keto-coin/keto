/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   KeystoreModuleManager.cpp
 * Author: Brett Chaldecott
 * 
 * Created on January 20, 2018, 4:40 PM
 */

#include <boost/dll/alias.hpp>
#include <boost/dll/shared_library.hpp>
#include <boost/shared_ptr.hpp>

#include "keto/common/Log.hpp"
#include "keto/common/MetaInfo.hpp"

#include "keto/keystore/KeystoreModuleManager.hpp"
#include "keto/keystore/KeyStoreService.hpp"
#include "keto/keystore/EventRegistry.hpp"
#include "include/keto/keystore/EventRegistry.hpp"

namespace keto {
namespace keystore {

KeystoreModuleManager::KeystoreModuleManager() {
}


KeystoreModuleManager::~KeystoreModuleManager() {
}

// meta methods
const std::string KeystoreModuleManager::getName() const {
    return "KeystoreModuleManager";
}

const std::string KeystoreModuleManager::getDescription() const {
    return "The keystore module manager responsible for managing the keystore process.";
}

const std::string KeystoreModuleManager::getVersion() const {
    return keto::common::MetaInfo::VERSION;
}

// lifecycle methods
void KeystoreModuleManager::start() {
    KeyStoreService::init();
    modules["KeystoreModule"] = std::make_shared<KeystoreModule>();
    EventRegistry::registerEventHandlers();
    KETO_LOG_INFO << "[KeystoreModuleManager] Started the KeystoreModuleManager";
}

void KeystoreModuleManager::stop() {
    EventRegistry::deregisterEventHandlers();
    modules.clear();
    KeyStoreService::fin();
    KETO_LOG_INFO << "[KeystoreModuleManager] The KeystoreModuleManager is being stopped";
}

const std::vector<std::string> KeystoreModuleManager::listModules() {
    std::vector<std::string> keys;
    std::transform(
        this->modules.begin(),
        this->modules.end(),
        std::back_inserter(keys),
        [](const std::map<std::string,std::shared_ptr<keto::module::ModuleInterface>>::value_type 
            &pair){return pair.first;});
    return keys;
}

const std::shared_ptr<keto::module::ModuleInterface> KeystoreModuleManager::getModule(const std::string& name) {
    return modules[name];
}

boost::shared_ptr<KeystoreModuleManager> KeystoreModuleManager::create_module() {
    return boost::shared_ptr<KeystoreModuleManager>(new KeystoreModuleManager());
}

BOOST_DLL_ALIAS(
    keto::keystore::KeystoreModuleManager::create_module,
    create_module                               
)


}
}
