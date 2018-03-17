/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TransactionMessageHelper.cpp
 * Author: ubuntu
 * 
 * Created on March 17, 2018, 4:21 AM
 */

#include "keto/transaction_common/TransactionMessageHelper.hpp"
#include "keto/common/MetaInfo.hpp"
#include "keto/asn1/HashHelper.hpp"
#include "keto/asn1/SignatureHelper.hpp"
#include "keto/transaction_common/Exception.hpp"

namespace keto {
namespace transaction_common {

TransactionMessageHelper::TransactionMessageHelper() {
    this->transactionMessage = (TransactionMessage_t*)calloc(1, sizeof *transactionMessage);
    this->transactionMessage->version = keto::common::MetaInfo::PROTOCOL_VERSION;
}


TransactionMessageHelper::TransactionMessageHelper(SignedTransaction_t* signedTransaction) {
    this->transactionMessage = (TransactionMessage_t*)calloc(1, sizeof *transactionMessage);
    this->transactionMessage->version = keto::common::MetaInfo::PROTOCOL_VERSION;
    this->transactionMessage->signedTransaction = *signedTransaction;
    this->transactionMessage->transactionHash = keto::asn1::HashHelper(
            signedTransaction->transactionHash);
    this->transactionMessage->signature = keto::asn1::SignatureHelper(
            signedTransaction->signature);
}


TransactionMessageHelper::TransactionMessageHelper(SignedTransaction_t* signedTransaction,
        const keto::asn1::HashHelper& sourceAccount, 
        const keto::asn1::HashHelper& targetAccount) {
    this->transactionMessage = (TransactionMessage_t*)calloc(1, sizeof *transactionMessage);
    this->transactionMessage->version = keto::common::MetaInfo::PROTOCOL_VERSION;
    this->transactionMessage->signedTransaction = *signedTransaction;
    this->transactionMessage->sourceAccount = sourceAccount;
    this->transactionMessage->targetAccount = targetAccount;
    this->transactionMessage->transactionHash = keto::asn1::HashHelper(
            signedTransaction->transactionHash);
    this->transactionMessage->signature = keto::asn1::SignatureHelper(
            signedTransaction->signature);
    
}


TransactionMessageHelper::TransactionMessageHelper(TransactionMessage_t* transactionMessage) :
    transactionMessage(transactionMessage) {
}


TransactionMessageHelper::~TransactionMessageHelper() {
    if (transactionMessage) {
        ASN_STRUCT_FREE(asn_DEF_TransactionMessage, transactionMessage);
        transactionMessage = 0;
    }
}


TransactionMessageHelper& TransactionMessageHelper::setSignedTransaction(
    SignedTransaction_t* signedTransaction) {
    this->transactionMessage->signedTransaction = *signedTransaction;
    this->transactionMessage->transactionHash = keto::asn1::HashHelper(
            signedTransaction->transactionHash);
    this->transactionMessage->signature = keto::asn1::SignatureHelper(
            signedTransaction->signature);
    
    return (*this);
}

TransactionMessageHelper& TransactionMessageHelper::setSourceAccount(
    const keto::asn1::HashHelper& sourceAccount) {
    this->transactionMessage->sourceAccount = sourceAccount;
    return (*this);
}

TransactionMessageHelper& TransactionMessageHelper::setTargetAccount(
    const keto::asn1::HashHelper& targetAccount) {
    this->transactionMessage->targetAccount = targetAccount;
    return (*this);
}

TransactionMessageHelper& TransactionMessageHelper::setStatus(const Status& status) {
    this->transactionMessage->currentStatus = status;
    return (*this);
}

TransactionMessageHelper& TransactionMessageHelper::addTransactionTrace(
    TransactionTrace_t* transactionTrace) {
    if (0!= ASN_SEQUENCE_ADD(&this->transactionMessage->transactionTrace,transactionTrace)) {
        BOOST_THROW_EXCEPTION(keto::transaction_common::TransactionTraceSequenceAddFailedException());
    }
    return (*this);
}

TransactionMessageHelper& TransactionMessageHelper::addChangeSet(
    SignedChangeSet_t* signedChangeSet) {
    
    if (0!= ASN_SEQUENCE_ADD(&this->transactionMessage->changeSet,signedChangeSet)) {
        BOOST_THROW_EXCEPTION(keto::transaction_common::SignedChangeSetSequenceAddFailedException());
    }
    return (*this);
}

TransactionMessageHelper::operator TransactionMessage_t&() {
    return (*this->transactionMessage);
}

TransactionMessageHelper::operator TransactionMessage_t*() {
    TransactionMessage_t* result = this->transactionMessage;
    this->transactionMessage = 0;
    return result;
}

TransactionMessageHelper::operator ANY_t*() {
    ANY_t* anyPtr = ANY_new_fromType(&asn_DEF_TransactionMessage, this->transactionMessage);
    if (!anyPtr) {
        BOOST_THROW_EXCEPTION(keto::transaction_common::ANYSerializationFailedException());
    }
    return anyPtr;
}

}
}
