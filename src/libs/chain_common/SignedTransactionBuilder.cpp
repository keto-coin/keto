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

#include <botan/pkcs8.h>
#include <botan/hash.h>
#include <botan/data_src.h>
#include <botan/pubkey.h>
#include <botan/rng.h>
#include <botan/auto_rng.h>

#include "PrivateKey.h"
#include "keto/asn1/BerEncodingHelper.hpp"
#include "keto/crypto/SignatureGenerator.hpp"
#include "keto/crypto/HashGenerator.hpp"
#include "keto/chain_common/SignedTransactionBuilder.hpp"


namespace keto {
    namespace chain_common {
        

SignedTransactionBuilder::~SignedTransactionBuilder() {
    if (this->signedTransaction) {
        ASN_STRUCT_FREE(asn_DEF_SignedTransaction, this->signedTransaction);
        this->signedTransaction = 0;
    }
}

std::shared_ptr<SignedTransactionBuilder> 
    SignedTransactionBuilder::createTransaction(
        const keto::asn1::PrivateKeyHelper& privateKeyHelper) {
    return std::shared_ptr<SignedTransactionBuilder>(
            new SignedTransactionBuilder(privateKeyHelper));
}

SignedTransactionBuilder& SignedTransactionBuilder::setTransaction(
    const std::shared_ptr<TransactionBuilder>& transactionBuilder) {
    keto::asn1::HashHelper hashHelper(
        keto::crypto::HashGenerator().generateHash(
        transactionBuilder->operator std::vector<uint8_t>&()));
    this->signedTransaction->transactionHash = hashHelper;
    Transaction* transaction = transactionBuilder->takePtr();
    this->signedTransaction->transaction = *transaction;
    free(transaction);
    return (*this);
}

keto::asn1::HashHelper SignedTransactionBuilder::getSourceAccount() {
    keto::asn1::HashHelper accountHash(
            this->signedTransaction->transaction.sourceAccount);
    return accountHash;
}
    
keto::asn1::HashHelper SignedTransactionBuilder::getHash() {
    keto::asn1::HashHelper hashHelper(this->signedTransaction->transactionHash);
    return hashHelper;
}

keto::asn1::SignatureHelper SignedTransactionBuilder::getSignature() {
    keto::asn1::SignatureHelper signatureHelper(this->signedTransaction->signature);
    return signatureHelper;
}

void SignedTransactionBuilder::sign() {
    
    keto::asn1::BerEncodingHelper key = this->privateKeyHelper.getKey();
    keto::crypto::SignatureGenerator generator((keto::crypto::SecureVector)key);
    keto::asn1::HashHelper hashHelper(this->signedTransaction->transactionHash);
    keto::asn1::SignatureHelper signatureHelper(generator.sign(hashHelper));
    this->signedTransaction->signature = signatureHelper;
}


SignedTransactionBuilder::operator std::vector<uint8_t>&() {
    serializeTransaction();
    return (std::vector<uint8_t>&)(*(this->serializationHelperPtr));
}

SignedTransactionBuilder::operator uint8_t*() {
    serializeTransaction();
    return (uint8_t*)(*(this->serializationHelperPtr));
}

SignedTransactionBuilder::operator SignedTransaction*() {
    SignedTransaction* result = this->signedTransaction;
    this->signedTransaction = NULL;
    return result;
}

size_t SignedTransactionBuilder::size() {
    serializeTransaction();
    return this->serializationHelperPtr->size();
}



SignedTransactionBuilder::SignedTransactionBuilder(
    const keto::asn1::PrivateKeyHelper& privateKeyHelper) : 
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