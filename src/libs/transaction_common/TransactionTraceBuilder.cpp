/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TransactionTraceBuilder.cpp
 * Author: ubuntu
 * 
 * Created on March 17, 2018, 5:04 AM
 */

#include "keto/transaction_common/TransactionTraceBuilder.hpp"

#include "keto/crypto/SignatureGenerator.hpp"
#include "keto/asn1/SignatureHelper.hpp"


namespace keto {
namespace transaction_common {

TransactionTraceBuilder::TransactionTraceBuilder(
    const keto::asn1::HashHelper& accountHash, keto::crypto::KeyLoader& keyloader) {
    this->transactionTrace = (TransactionTrace_t*)calloc(1, sizeof *transactionTrace);
    this->transactionTrace->traceHash = accountHash;
    keto::crypto::SignatureGenerator generator(keyloader);
    keto::asn1::SignatureHelper signatureHelper(generator.sign(accountHash));
    this->transactionTrace->signature = signatureHelper;
    
}


TransactionTraceBuilder::~TransactionTraceBuilder() {
    if (transactionTrace) {
        ASN_STRUCT_FREE(asn_DEF_TransactionTrace, transactionTrace);
        transactionTrace = 0;
    }
}

TransactionTraceBuilderPtr TransactionTraceBuilder::createTransactionTrace(
    const keto::asn1::HashHelper& accountHash, keto::crypto::KeyLoader& keyloader) {
    return TransactionTraceBuilderPtr(
            new TransactionTraceBuilder(accountHash,keyloader));
}

TransactionTraceBuilder::operator TransactionTrace_t*() {
    TransactionTrace_t* result = this->transactionTrace;
    this->transactionTrace = 0;
    return result;
}

TransactionTraceBuilder::operator TransactionTrace_t&() {
    return *this->transactionTrace;
}


}
}