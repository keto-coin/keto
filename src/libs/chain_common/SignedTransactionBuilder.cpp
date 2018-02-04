/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SignedTransactionBuilder.cpp
 * Author: ubuntu
 * 
 * Created on January 31, 2018, 7:24 AM
 */

#include <botan/hash.h>
#include "keto/chain_common/SignedTransactionBuilder.hpp"
#include "include/keto/chain_common/TransactionBuilder.hpp"

namespace keto {
    namespace chain_common {
        

SignedTransactionBuilder::~SignedTransactionBuilder() {
    if (this->signedTransaction) {
        ASN_STRUCT_FREE(asn_DEF_SignedTransaction, this->signedTransaction);
    }
}

std::shared_ptr<SignedTransactionBuilder> 
    SignedTransactionBuilder::createTransaction(
        const keto::crypto::PrivateKeyHelper& privateKeyHelper) {
    return std::shared_ptr<SignedTransactionBuilder>(
            new SignedTransactionBuilder(privateKeyHelper));
}

SignedTransactionBuilder& SignedTransactionBuilder::setTransaction(
    const std::shared_ptr<TransactionBuilder> transactionBuilder) {
    std::unique_ptr<Botan::HashFunction> hash256(Botan::HashFunction::create("SHA-256"));
    keto::crypto::SecureVector vector = 
            hash256->process((const std::vector<uint8_t>)*transactionBuilder);
    this->signedTransaction->transactionHash = keto::asn1::HashHelper(vector);
    Transaction* transaction = transactionBuilder->takePtr();
    this->signedTransaction->transaction = *transaction;
    free(transaction);
    return (*this);
}

void SignedTransactionBuilder::sign() {
    
}

SignedTransactionBuilder::operator std::vector<uint8_t>&() {
    serializeTransaction();
    return (std::vector<uint8_t>&)(*(this->serializationHelperPtr));
}

SignedTransactionBuilder::operator uint8_t*() {
    serializeTransaction();
    return (uint8_t*)(*(this->serializationHelperPtr));
}

size_t SignedTransactionBuilder::size() {
    serializeTransaction();
    return this->serializationHelperPtr->size();
}



SignedTransactionBuilder::SignedTransactionBuilder(
    const keto::crypto::PrivateKeyHelper& privateKeyHelper) : 
    privateKeyHelper(privateKeyHelper) {
    
    this->signedTransaction = (SignedTransaction*)calloc(1, sizeof *signedTransaction);
    this->signedTransaction->version = keto::common::MetaInfo::PROTOCOL_VERSION;
    
    
}


void SignedTransactionBuilder::serializeTransaction() {
    if (!this->serializationHelperPtr) {
        this->serializationHelperPtr = 
                std::make_shared<keto::asn1::SerializationHelper<SignedTransaction>>(
                this->signedTransaction,&asn_DEF_SignedTransaction);
    }
}


}
}