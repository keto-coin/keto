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
#include "include/keto/block/BlockProducer.hpp"
#include "include/keto/block/Exception.hpp"

namespace keto {
namespace block {

static BlockProducerPtr singleton;
static std::shared_ptr<std::thread> producerThreadPtr; 
    

BlockProducer::BlockProducer() : currentState(State::inited) {
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


void BlockProducer::generateBlock(const std::deque<keto::proto::Transaction>& transactions) {
    
}

}
}