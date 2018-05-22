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
#include "keto/block/TransactionProcessor.hpp"
#include "keto/block/BlockProducer.hpp"

#include "keto/transaction_common/MessageWrapperProtoHelper.hpp"
#include "keto/transaction_common/TransactionProtoHelper.hpp"

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
    
    keto::transaction_common::MessageWrapperProtoHelper messageWrapperProtoHelper(
        messageWrapper);
    
    keto::transaction_common::TransactionProtoHelperPtr transactionProtoHelperPtr
            = messageWrapperProtoHelper.getTransaction();
    {
        std::lock_guard<std::mutex> guard(getAccountLock(
            keto::server_common::VectorUtils().copyStringToVector(
        transactionProtoHelperPtr->operator keto::proto::Transaction&().active_account())));
        transactionProtoHelperPtr->operator =(
            TransactionProcessor::getInstance()->processTransaction(
            transactionProtoHelperPtr->operator keto::proto::Transaction&()));
        BlockProducer::getInstance()->addTransaction(
            transactionProtoHelperPtr->operator keto::proto::Transaction&());
    }
    // move transaction to next phase and submit to router
    messageWrapper = messageWrapperProtoHelper.operator keto::proto::MessageWrapper();
    messageWrapperProtoHelper.setTransaction(transactionProtoHelperPtr);
    keto::server_common::triggerEvent(keto::server_common::toEvent<keto::proto::MessageWrapper>(
            keto::server_common::Events::UPDATE_STATUS_ROUTE_MESSSAGE,
            messageWrapper));
    
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