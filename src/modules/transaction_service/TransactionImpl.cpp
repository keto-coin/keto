/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TransactionImpl.cpp
 * Author: ubuntu
 * 
 * Created on February 26, 2018, 1:06 PM
 */

#include "keto/transaction/TransactionImpl.hpp"
#include "keto/transaction/TransactionWrapper.hpp"
#include "keto/transaction/TransactionServiceModule.hpp"

namespace keto {
namespace transaction {


TransactionImpl::TransactionImpl(TransactionServiceModule& transactionService) :
    transactionService(transactionService), complete(false) {
}


TransactionImpl::~TransactionImpl() {
    if (!complete) {
        complete = true;
        transactionService.rollback();
    }
}

void TransactionImpl::commit() {
    if (!complete) {
        complete = true;
        transactionService.commit();
    }
}

void TransactionImpl::rollback() {
    if (!complete) {
        complete = true;
        transactionService.rollback();
    }
}
    

}
}