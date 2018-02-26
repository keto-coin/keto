/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TransactionServiceModule.cpp
 * Author: ubuntu
 * 
 * Created on February 26, 2018, 8:22 AM
 */


#include "keto/transaction/TransactionWrapper.hpp"
#include "keto/transaction/TransactionImpl.hpp"
#include "keto/transaction/Exception.hpp"
#include "keto/transaction/TransactionServiceModule.hpp"
#include "keto/common/MetaInfo.hpp"

namespace keto {
namespace transaction {

thread_local TransactionWrapperPtr TransactionServiceModule::transactionWrapper;
    
TransactionServiceModule::TransactionServiceModule() {
}


TransactionServiceModule::~TransactionServiceModule() {
}

// meta methods
const std::string TransactionServiceModule::getName() const {
    return "TransactionService";    
}


const std::string TransactionServiceModule::getDescription() const {
    return "Transaction Service Description";
}
const std::string TransactionServiceModule::getVersion() const {
    return keto::common::MetaInfo::VERSION;
}

// transaction methods
TransactionPtr TransactionServiceModule::createTransaction() {
    if (transactionWrapper) {
        BOOST_THROW_EXCEPTION(DuplicateTransactionException());
    }
    transactionWrapper = std::shared_ptr<TransactionWrapper>(new TransactionWrapper());
    return TransactionPtr(new TransactionImpl(*this));
}

void TransactionServiceModule::enlistResource(Resource& resource) {
    if (!transactionWrapper) {
        BOOST_THROW_EXCEPTION(NoTransactionException());
    }
    transactionWrapper->enlist(resource);
}


void TransactionServiceModule::commit() {
    if (!transactionWrapper) {
        BOOST_THROW_EXCEPTION(NoTransactionException());
    }
    transactionWrapper->commit();
    transactionWrapper.reset();
}


void TransactionServiceModule::rollback() {
    if (!transactionWrapper) {
        BOOST_THROW_EXCEPTION(NoTransactionException());
    }
    transactionWrapper->rollback();
    transactionWrapper.reset();
}
    

}
}