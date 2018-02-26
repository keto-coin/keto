/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TransactionServiceModuleManager.cpp
 * Author: ubuntu
 * 
 * Created on February 26, 2018, 2:17 PM
 */

#include <boost/dll/alias.hpp>
#include <boost/dll/shared_library.hpp>
#include <boost/shared_ptr.hpp>

#include "keto/transaction/TransactionWrapper.hpp"
#include "keto/transaction/TransactionService.hpp"
#include "keto/transaction/TransactionServiceModuleManager.hpp"
#include "keto/common/MetaInfo.hpp"
#include "keto/common/Log.hpp"

namespace keto {
namespace transaction {


TransactionServiceModuleManager::TransactionServiceModuleManager() {
}

TransactionServiceModuleManager::~TransactionServiceModuleManager() {
}


// meta methods
const std::string TransactionServiceModuleManager::getName() const {
    return "TransactionServiceModuleManager";
}


const std::string TransactionServiceModuleManager::getDescription() const {
    return "The Transaction Service for KETO";
}


const std::string TransactionServiceModuleManager::getVersion() const {
    return keto::common::MetaInfo::VERSION;
}


// lifecycle methods
void TransactionServiceModuleManager::start() {
    modules[keto::transaction::TransactionService::KETO_TRANSACTION_MANAGER] = 
            std::make_shared<TransactionServiceModule>();
    KETO_LOG_INFO << "[TransactionService] The transaction service has been started";
    
}

void TransactionServiceModuleManager::stop() {
    modules.clear();
    KETO_LOG_INFO << "[TransactionService] The transaction service is being stopped";
}

const std::vector<std::string> TransactionServiceModuleManager::listModules() {
    std::vector<std::string> keys;
    std::transform(
        this->modules.begin(),
        this->modules.end(),
        std::back_inserter(keys),
        [](const std::map<std::string,std::shared_ptr<keto::module::ModuleInterface>>::value_type 
            &pair){return pair.first;});
    return keys;

}


const std::shared_ptr<keto::module::ModuleInterface> TransactionServiceModuleManager::getModule(const std::string& name) {
    return modules[name];
}

boost::shared_ptr<TransactionServiceModuleManager> TransactionServiceModuleManager::create_module() {
    return boost::shared_ptr<TransactionServiceModuleManager>(new TransactionServiceModuleManager());
}

BOOST_DLL_ALIAS(
    keto::transaction::TransactionServiceModuleManager::create_module,
    create_module                          
)

}
}