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
#include <iostream>

#include "keto/block/TransactionProcessor.hpp"
#include "keto/transaction_common/ActionHelper.hpp"
#include "keto/transaction_common/TransactionProtoHelper.hpp"

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

keto::proto::Transaction TransactionProcessor::processTransaction(keto::proto::Transaction& transaction) {
    keto::transaction_common::TransactionProtoHelper transactionProtoHelper(transaction);
    
    std::cout << "Before looping through the actions" << std::endl; 
    if (transactionProtoHelper.getTransactionMessageHelper() && 
            transactionProtoHelper.getTransactionMessageHelper()->getSignedTransaction() &&
            transactionProtoHelper.getTransactionMessageHelper()->getSignedTransaction()->getTransaction()) {
        std::vector<keto::transaction_common::ActionHelperPtr> actions = 
            transactionProtoHelper.getTransactionMessageHelper()->getSignedTransaction()->getTransaction()->getActions();    
        for (keto::transaction_common::ActionHelperPtr action : actions) {
            std::cout << "The action is contract : " << action->getContract().getHash(keto::common::HEX) << std::endl;
        }
        
    }
    
    //transactionProtoHelper.getTransactionMessageHelper()
    return transactionProtoHelper;
}


}
}