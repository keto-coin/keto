/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TransactionBuilder.cpp
 * Author: brett chaldecott
 * 
 * Created on January 30, 2018, 3:04 PM
 */

#include <memory>
#include <stdlib.h>

#include "constr_TYPE.h"

#include "keto/chain_common/TransactionBuilder.hpp"
#include "keto/common/MetaInfo.hpp"
#include "keto/asn1/TimeHelper.hpp"


namespace keto {
namespace chain_common {


TransactionBuilder::TransactionBuilder() {
    this->transaction = (Transaction*)calloc(1, sizeof *transaction);
    this->transaction->version = keto::common::MetaInfo::PROTOCOL_VERSION;
    this->transaction->date = (UTCTime_t)keto::asn1::TimeHelper();
}

TransactionBuilder::~TransactionBuilder() {
    ASN_STRUCT_FREE(asn_DEF_Transaction, this->transaction);
}

std::shared_ptr<TransactionBuilder> TransactionBuilder::createTransaction() {
    return std::shared_ptr<TransactionBuilder>(new TransactionBuilder());
}

TransactionBuilder& TransactionBuilder::setValue(const keto::asn1::NumberHelper& numberHelper) {
    this->transaction->value = (Number_t)numberHelper;
    return (*this);
}


keto::asn1::NumberHelper TransactionBuilder::getValue() {
    return this->transaction->value;
}


TransactionBuilder::operator std::vector<uint8_t>&() {
    serializeTransaction();
    return (std::vector<uint8_t>&)(*(this->serializationHelperPtr));
}


TransactionBuilder::operator uint8_t*() {
    serializeTransaction();
    return (uint8_t*)(*(this->serializationHelperPtr));
}


size_t TransactionBuilder::size() {
    serializeTransaction();
    return this->serializationHelperPtr->size();
}



void TransactionBuilder::serializeTransaction() {
    if (!this->serializationHelperPtr) {
        this->serializationHelperPtr = 
                std::make_shared<keto::asn1::SerializationHelper<Transaction>>(
                this->transaction,&asn_DEF_Transaction);
    }
}
}
}