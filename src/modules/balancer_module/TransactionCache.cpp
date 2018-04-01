/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TransactionCache.cpp
 * Author: ubuntu
 * 
 * Created on March 31, 2018, 4:23 PM
 */

#include <condition_variable>
#include <set>

#include "keto/balancer/TransactionCache.hpp"
#include "include/keto/balancer/TransactionCache.hpp"

namespace keto {
namespace balancer {

static TransactionCachePtr singleton;    

TransactionCache::TransactionCache() {
}

TransactionCache::~TransactionCache() {
}

//void set
TransactionCachePtr TransactionCache::init() {
    return singleton = std::make_shared<TransactionCache>();
}

TransactionCachePtr TransactionCache::getInstance() {
    return singleton;
}

void TransactionCache::fin() {
    singleton.reset();
}

bool TransactionCache::isProcessed(TransactionIdHashVector transactionId) {
    std::lock_guard<std::mutex> guard(this->classMutex);
    return processedTransactions.count(transactionId);
}

void TransactionCache::processed(TransactionIdHashVector transactionId) {
    std::lock_guard<std::mutex> guard(this->classMutex);
    this->processedTransactions.insert(transactionId);
}


}
}