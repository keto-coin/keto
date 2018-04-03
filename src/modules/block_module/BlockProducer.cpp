/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BlockProducer.cpp
 * Author: ubuntu
 * 
 * Created on April 2, 2018, 10:38 AM
 */

#include "keto/block/BlockProducer.hpp"

#include "keto/common/Log.hpp"

#include "keto/environment/EnvironmentManager.hpp"
#include "keto/environment/Config.hpp"

#include "keto/block_db/BlockBuilder.hpp"
#include "keto/block_db/SignedBlockBuilder.hpp"
#include "keto/block_db/BlockChainStore.hpp"

#include "keto/block/Constants.hpp"

#include "include/keto/block/BlockProducer.hpp"
#include "include/keto/block/Exception.hpp"

#include "keto/transaction/Transaction.hpp"
#include "keto/server_common/TransactionHelper.hpp"

#include "keto/transaction_common/TransactionMessageHelper.hpp"
#include "keto/transaction_common/ChangeSetBuilder.hpp"
#include "keto/transaction_common/SignedChangeSetBuilder.hpp"
#include "keto/transaction_common/TransactionProtoHelper.hpp"


#include "keto/chain_common/ActionBuilder.hpp"
#include "keto/chain_common/TransactionBuilder.hpp"
#include "keto/chain_common/SignedTransactionBuilder.hpp"

#include "keto/server_common/EventUtils.hpp"
#include "keto/server_common/Events.hpp"
#include "keto/server_common/EventServiceHelpers.hpp"


namespace keto {
namespace block {

static BlockProducerPtr singleton;
static std::shared_ptr<std::thread> producerThreadPtr; 
    

BlockProducer::BlockProducer() : currentState(State::inited) {
    std::shared_ptr<keto::environment::Config> config = 
            keto::environment::EnvironmentManager::getInstance()->getConfig();
    if (!config->getVariablesMap().count(Constants::PRIVATE_KEY)) {
        BOOST_THROW_EXCEPTION(keto::block::PrivateKeyNotConfiguredException());
    }
    std::string privateKeyPath = 
            config->getVariablesMap()[Constants::PRIVATE_KEY].as<std::string>();
    if (!config->getVariablesMap().count(Constants::PUBLIC_KEY)) {
        BOOST_THROW_EXCEPTION(keto::block::PrivateKeyNotConfiguredException());
    }
    std::string publicKeyPath = 
            config->getVariablesMap()[Constants::PUBLIC_KEY].as<std::string>();
    keyLoaderPtr = std::make_shared<keto::crypto::KeyLoader>(privateKeyPath,
            publicKeyPath);
}

BlockProducer::~BlockProducer() {
}

BlockProducerPtr BlockProducer::init() {
    singleton = std::make_shared<BlockProducer>();
    producerThreadPtr = std::shared_ptr<std::thread>(new std::thread(
        []
        {
            singleton->run();
        }));
    return singleton;
}

void BlockProducer::fin() {
    singleton->terminate();
    producerThreadPtr->join();
    producerThreadPtr.reset();
    singleton.reset();
}

BlockProducerPtr BlockProducer::getInstance() {
    return singleton;
}

void BlockProducer::run() {
    while(this->checkState() != State::terminated) {
        generateBlock(this->getTransactions());
    }
}

void BlockProducer::terminate() {
    std::unique_lock<std::mutex> uniqueLock(this->classMutex);
    this->currentState = State::terminated;
    this->stateCondition.notify_all();
}

void BlockProducer::addTransaction(keto::proto::Transaction transaction) {
    std::lock_guard<std::mutex> guard(this->classMutex);
    if (this->currentState == State::terminated) {
        BOOST_THROW_EXCEPTION(keto::block::BlockProducerTerminatedException());
    }
    this->transactions.push_back(transaction);
}

BlockProducer::State BlockProducer::checkState() {
    std::unique_lock<std::mutex> uniqueLock(this->classMutex);
    KETO_LOG_DEBUG << "[BlockProducer] wait";
    this->stateCondition.wait_for(uniqueLock,std::chrono::milliseconds(20 * 1000));
    KETO_LOG_DEBUG << "[Block Producer] run";
    return this->currentState;
}

std::deque<keto::proto::Transaction> BlockProducer::getTransactions() {
    std::unique_lock<std::mutex> uniqueLock(this->classMutex);
    std::deque<keto::proto::Transaction> transactions = this->transactions;
    this->transactions.clear();
    return transactions;
}


void BlockProducer::generateBlock(std::deque<keto::proto::Transaction> transactions) {
    // create a new transaction
    keto::transaction::TransactionPtr transactionPtr = keto::server_common::createTransaction();
    
    keto::asn1::HashHelper parentHash = keto::block_db::BlockChainStore::getInstance()->getParentHash();
    keto::block_db::BlockBuilderPtr blockBuilderPtr = 
            std::make_shared<keto::block_db::BlockBuilder>(parentHash);
    for (keto::proto::Transaction& transaction : transactions) {
        keto::transaction_common::TransactionProtoHelper transactionProtoHelper(
            keto::server_common::fromEvent<keto::proto::Transaction>(
            keto::server_common::processEvent(keto::server_common::toEvent<keto::proto::Transaction>(
            keto::server_common::Events::APPLY_ACCOUNT_TRANSACTION_MESSAGE,transaction))));
        
        blockBuilderPtr->addTransactionMessage(*transactionProtoHelper.getTransactionMessageHelper());
    }
    keto::block_db::SignedBlockBuilderPtr signedBlockBuilderPtr(new keto::block_db::SignedBlockBuilder(
            blockBuilderPtr->operator Block_t*(),
            keyLoaderPtr));
    signedBlockBuilderPtr->sign();
    
    KETO_LOG_INFO << "Write a block";
    keto::block_db::BlockChainStore::getInstance()->writeBlock(*signedBlockBuilderPtr);
    KETO_LOG_INFO << "Wrote a block [" << 
            keto::block_db::BlockChainStore::getInstance()->getBlockCount() << "][" <<
            keto::block_db::BlockChainStore::getInstance()->getParentHash().getHash(keto::common::HEX)
            << "]";
    
    transactionPtr->commit();
    
}

}
}