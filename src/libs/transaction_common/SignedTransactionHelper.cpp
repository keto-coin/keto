/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SignedTransactionHelper.cpp
 * Author: ubuntu
 * 
 * Created on April 3, 2018, 9:39 AM
 */

#include "keto/transaction_common/SignedTransactionHelper.hpp"
#include "include/keto/transaction_common/SignedTransactionHelper.hpp"

namespace keto {
namespace transaction_common {

SignedTransactionHelper::SignedTransactionHelper(SignedTransaction_t* signedTransaction) :
    signedTransaction(signedTransaction) {
}

SignedTransactionHelper::~SignedTransactionHelper() {
}

keto::asn1::HashHelper SignedTransactionHelper::getHash() {
    return this->signedTransaction->transactionHash;
}

keto::asn1::SignatureHelper SignedTransactionHelper::getSignature() {
    return this->signedTransaction->signature;
}

TransactionHelperPtr SignedTransactionHelper::getTransaction() {
    return TransactionHelperPtr(new TransactionHelper(&this->signedTransaction->transaction)); 
}

}
}
