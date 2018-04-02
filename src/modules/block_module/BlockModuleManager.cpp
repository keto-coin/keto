/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BlockModuleManager.cpp
 * Author: Brett Chaldecott
 * 
 * Created on February 10, 2018, 3:34 PM
 */

#include <boost/dll/alias.hpp>
#include <boost/dll/shared_library.hpp>
#include <boost/shared_ptr.hpp>

#include "keto/common/Log.hpp"
#include "keto/common/MetaInfo.hpp"
#include "keto/block/BlockModuleManager.hpp"
#include "keto/block/StorageManager.hpp"

#include "keto/transaction/Transaction.hpp"
#include "keto/server_common/TransactionHelper.hpp"
#include "keto/server_common/Constants.hpp"
#include "keto/server_common/ServiceRegistryHelper.hpp"
#include "keto/block/BlockService.hpp"
#include "keto/block/EventRegistry.hpp"
#include "keto/block/TransactionProcessor.hpp"
#include "keto/block/BlockProducer.hpp"
#include "include/keto/block/BlockProducer.hpp"


namespace keto {
namespace block {

BlockModuleManager::BlockModuleManager() {
}

BlockModuleManager::~BlockModuleManager() {
}

// meta methods
const std::string BlockModuleManager::getName() const {
    return "BlockModuleManager";
}

const std::string BlockModuleManager::getDescription() const {
    return "The block module manager responsible for managing the block production.";
}

const std::string BlockModuleManager::getVersion() const {
    return keto::common::MetaInfo::VERSION;
}

// lifecycle methods
void BlockModuleManager::start() {
    BlockProducer::init();
    TransactionProcessor::init();
    StorageManager::init();
    modules["blockModule"] = std::make_shared<BlockModule>();
    BlockService::init();
    EventRegistry::registerEventHandlers();
    KETO_LOG_INFO << "[BlockModuleManager] Started the BlockModuleManager";
}

void BlockModuleManager::postStart() {
    KETO_LOG_INFO << "[BlockModuleManager] Block manager post start has been called";
    keto::transaction::TransactionPtr transactionPtr = keto::server_common::createTransaction();
    BlockService::getInstance()->genesis();
    transactionPtr->commit();
    
    KETO_LOG_INFO << "[BlockModuleManager] Register the services";
    keto::server_common::registerService(keto::server_common::Constants::SERVICE::BLOCK);
    KETO_LOG_INFO << "[BlockModuleManager] After registering the services";
}

void BlockModuleManager::stop() {
    EventRegistry::deregisterEventHandlers();
    BlockService::fin();
    modules.clear();
    TransactionProcessor::fin();
    BlockProducer::fin();
    StorageManager::fin();
    KETO_LOG_INFO << "[BlockModuleManager] The BlockModuleManager is being stopped";
}

const std::vector<std::string> BlockModuleManager::listModules() {
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
    BlockModuleManager::getModule(const std::string& name) {
    return modules[name];
}

boost::shared_ptr<BlockModuleManager> BlockModuleManager::create_module() {
    return boost::shared_ptr<BlockModuleManager>(new BlockModuleManager());    

}


BOOST_DLL_ALIAS(
    keto::block::BlockModuleManager::create_module,
    create_module
)


}
}
