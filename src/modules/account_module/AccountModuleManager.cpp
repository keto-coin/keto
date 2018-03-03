/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AccountModuleManager.cpp
 * Author: ubuntu
 * 
 * Created on March 3, 2018, 12:17 PM
 */

#include <boost/dll/alias.hpp>
#include <boost/dll/shared_library.hpp>
#include <boost/shared_ptr.hpp>


#include "keto/common/Log.hpp"
#include "keto/account/AccountModuleManager.hpp"
#include "keto/account/AccountModule.hpp"

namespace keto {
namespace account {

AccountModuleManager::AccountModuleManager() {
}

AccountModuleManager::~AccountModuleManager() {
}


// meta methods
const std::string AccountModuleManager::getName() const {
    return "AccountModuleManager";
}

const std::string AccountModuleManager::getDescription() const {
    return "The account module manager responsible for managing the balancer and filter.";
}

const std::string AccountModuleManager::getVersion() const {
    return keto::common::MetaInfo::VERSION;
}

// lifecycle methods
void AccountModuleManager::start() {
    modules["accountModule"] = std::make_shared<AccountModule>();
    KETO_LOG_INFO << "[AccountModuleManager] Started the AccountModuleManager";
}

void AccountModuleManager::stop() {
    modules.clear();
    KETO_LOG_INFO << "[AccountModuleManager] The AccountModuleManager is being stopped";
}

const std::vector<std::string> AccountModuleManager::listModules() {
    std::vector<std::string> keys;
    std::transform(
        this->modules.begin(),
        this->modules.end(),
        std::back_inserter(keys),
        [](const std::map<std::string,std::shared_ptr<keto::module::ModuleInterface>>::value_type 
            &pair){return pair.first;});
    return keys;
}

const std::shared_ptr<keto::module::ModuleInterface> 
    AccountModuleManager::getModule(const std::string& name) {
    return modules[name];
}

boost::shared_ptr<AccountModuleManager> AccountModuleManager::create_module() {
    return boost::shared_ptr<AccountModuleManager>(new AccountModuleManager());    
}

BOOST_DLL_ALIAS(
    keto::account::AccountModuleManager::create_module,
    create_module
)

}
}
