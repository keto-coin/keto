/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TransactionProtoHelper.cpp
 * Author: ubuntu
 * 
 * Created on March 19, 2018, 7:59 AM
 */

#include "keto/transaction_common/TransactionProtoHelper.hpp"

#include "keto/server_common/VectorUtils.hpp"
#include "keto/crypto/HashGenerator.hpp"
#include "keto/crypto/SignatureGenerator.hpp"
#include "keto/crypto/SecureVectorUtils.hpp"
#include "include/keto/transaction_common/TransactionProtoHelper.hpp"


namespace keto {
namespace transaction_common {
    

TransactionProtoHelper::TransactionProtoHelper() {
}

TransactionProtoHelper::TransactionProtoHelper(const keto::proto::Transaction& transaction) {
    this->transaction.CopyFrom(transaction);
}

TransactionProtoHelper::TransactionProtoHelper(
        const TransactionMessageHelperPtr& transactionMessageHelper) {
    keto::asn1::HashHelper hashHelper = transactionMessageHelper->getHash();
    transaction.set_transaction_hash(
        hashHelper.operator keto::crypto::SecureVector().data(),
        hashHelper.operator keto::crypto::SecureVector().size());
    keto::asn1::SignatureHelper signatureHelper = transactionMessageHelper->getSignature();
    transaction.set_transaction_signature(
        signatureHelper.operator std::vector<uint8_t>().data(),
        signatureHelper.operator std::vector<uint8_t>().size());
    hashHelper = transactionMessageHelper->getSourceAccount();
    transaction.set_active_account(
        hashHelper.operator keto::crypto::SecureVector().data(),
        hashHelper.operator keto::crypto::SecureVector().size());
    transaction.set_status(keto::proto::INIT);
    std::vector<uint8_t> serializedTransaction = 
        transactionMessageHelper->operator std::vector<uint8_t>();
    transaction.set_asn1_transaction_message(
        serializedTransaction.data(),serializedTransaction.size());
}


TransactionProtoHelper::~TransactionProtoHelper() {
}

TransactionProtoHelper& TransactionProtoHelper::setTransaction(
    const TransactionMessageHelperPtr& transactionMessageHelper) {
    
    keto::asn1::HashHelper hashHelper = transactionMessageHelper->getHash();
    transaction.set_transaction_hash(
        hashHelper.operator keto::crypto::SecureVector().data(),
        hashHelper.operator keto::crypto::SecureVector().size());
    keto::asn1::SignatureHelper signatureHelper = transactionMessageHelper->getSignature();
    transaction.set_transaction_signature(
        signatureHelper.operator std::vector<uint8_t>().data(),
        signatureHelper.operator std::vector<uint8_t>().size());
    hashHelper = transactionMessageHelper->getSourceAccount();
    transaction.set_active_account(
        hashHelper.operator keto::crypto::SecureVector().data(),
        hashHelper.operator keto::crypto::SecureVector().size());
    transaction.set_status(keto::proto::INIT);
    std::vector<uint8_t> serializedTransaction = 
        transactionMessageHelper->operator std::vector<uint8_t>();
    transaction.set_asn1_transaction_message(
        serializedTransaction.data(),serializedTransaction.size());
    
    return (*this);
}

TransactionProtoHelper& TransactionProtoHelper::setTransaction(
        const std::string& buffer) {
    transaction.ParseFromString(buffer);
    return (*this);
}

TransactionProtoHelper::operator std::string() {
    std::string buffer;
    transaction.SerializeToString(&buffer);
    return buffer;
}

TransactionProtoHelper::operator keto::proto::Transaction&() {
    return this->transaction;
}


TransactionProtoHelper& TransactionProtoHelper::operator = (const keto::proto::Transaction& transaction) {
    this->transaction.CopyFrom(transaction);
    return (*this);
}

TransactionMessageHelperPtr TransactionProtoHelper::getTransactionMessageHelper() {
    return TransactionMessageHelperPtr(
            new TransactionMessageHelper(this->transaction.asn1_transaction_message()));
}

    
}
}