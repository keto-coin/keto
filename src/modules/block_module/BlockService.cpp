/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BlockService.cpp
 * Author: ubuntu
 * 
 * Created on March 8, 2018, 3:04 AM
 */

#include <condition_variable>

#include <iostream>

#include "Protocol.pb.h"
#include "BlockChain.pb.h"

#include "keto/block/BlockService.hpp"
#include "keto/block_db/BlockChainStore.hpp"

#include "keto/environment/EnvironmentManager.hpp"
#include "keto/environment/Config.hpp"
#include "keto/block/Constants.hpp"
#include "keto/block/GenesisReader.hpp"
#include "keto/block/GenesisLoader.hpp"
#include "include/keto/block/GenesisLoader.hpp"

#include "keto/server_common/Events.hpp"
#include "keto/server_common/EventServiceHelpers.hpp"
#include "include/keto/block/TransactionProcessor.hpp"
#include "include/keto/block/BlockProducer.hpp"

namespace keto {
namespace block {

static std::shared_ptr<BlockService> singleton;


BlockService::BlockService() {
}

BlockService::~BlockService() {
}

std::shared_ptr<BlockService> BlockService::init() {
    return singleton = std::make_shared<BlockService>();
}

void BlockService::fin() {
    singleton.reset();
}

std::shared_ptr<BlockService> BlockService::getInstance() {
    return singleton;
}

void BlockService::genesis() {
    if (keto::block_db::BlockChainStore::getInstance()->requireGenesis()) {
        std::shared_ptr<keto::environment::Config> config = 
            keto::environment::EnvironmentManager::getInstance()->getConfig();
    
        if (!config->getVariablesMap().count(Constants::GENESIS_CONFIG)) {
            return;
        }
        // genesis configuration
        boost::filesystem::path genesisConfig =  
                keto::environment::EnvironmentManager::getInstance()->getEnv()->getInstallDir() / 
                config->getVariablesMap()[Constants::GENESIS_CONFIG].as<std::string>();
        
        if (!boost::filesystem::exists(genesisConfig)) {
            return;
        }
        GenesisReader reader(genesisConfig);
        GenesisLoader loader(reader);
        loader.load();
    }
}

keto::event::Event BlockService::blockMessage(const keto::event::Event& event) {
    keto::proto::MessageWrapper  messageWrapper = 
            keto::server_common::fromEvent<keto::proto::MessageWrapper>(event);
    std::cout << "The block service says hi" << std::endl;
    
    keto::proto::Transaction transaction;
    messageWrapper.msg().UnpackTo(&transaction);
    {
        std::lock_guard<std::mutex> guard(getAccountLock(
            keto::server_common::VectorUtils().copyStringToVector(transaction.active_account())));
        transaction.set_asn1_transaction_message(
            TransactionProcessor::getInstance()->processTransaction(
            transaction.asn1_transaction_message()));
        BlockProducer::getInstance()->addTransaction(transaction);
    }
    keto::proto::MessageWrapperResponse response;
    response.set_success(true);
    response.set_result("balanced");
    return keto::server_common::toEvent<keto::proto::MessageWrapperResponse>(response);
}



std::mutex& BlockService::getAccountLock(const AccountHashVector& accountHash) {
    std::lock_guard<std::mutex> guard(this->classMutex);
    if (!accountLocks.count(accountHash)) {
        accountLocks[accountHash];
    }
    return accountLocks[accountHash];
}


}
}