/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TransactionProcessor.cpp
 * Author: ubuntu
 * 
 * Created on April 2, 2018, 9:00 AM
 */

#include <condition_variable>

#include "keto/block/TransactionProcessor.hpp"

namespace keto {
namespace block {

static TransactionProcessorPtr singleton;

TransactionProcessor::TransactionProcessor() {
}

TransactionProcessor::~TransactionProcessor() {
}

TransactionProcessorPtr TransactionProcessor::init() {
    return singleton = std::make_shared<TransactionProcessor>();
}

void TransactionProcessor::fin() {
    singleton.reset();
}

TransactionProcessorPtr TransactionProcessor::getInstance() {
    return singleton;
}

std::string TransactionProcessor::processTransaction(std::string transaction) {
    
    return transaction;
}


}
}