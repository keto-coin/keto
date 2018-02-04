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
#include "keto/chain_common/Exception.hpp"


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

long TransactionBuilder::getVersion() {
    return this->transaction->version;
}

keto::asn1::TimeHelper TransactionBuilder::getDate() {
    return this->transaction->date;
}

TransactionBuilder& TransactionBuilder::setValue(const keto::asn1::NumberHelper& numberHelper) {
    this->transaction->value = (Number_t)numberHelper;
    return (*this);
}

keto::asn1::NumberHelper TransactionBuilder::getValue() {
    return this->transaction->value;
}

TransactionBuilder& TransactionBuilder::setParent(const keto::asn1::HashHelper& hashHelper) {
    this->transaction->parent = (Hash_t)hashHelper;
    return (*this);
}

keto::asn1::HashHelper TransactionBuilder::getParent() {
    return this->transaction->parent;
}


TransactionBuilder& TransactionBuilder::setSourceAccount(const keto::asn1::HashHelper& hashHelper) {
    this->transaction->sourceAccount = (Hash_t)hashHelper;
    return (*this);
}


keto::asn1::HashHelper TransactionBuilder::getSourceAccount() {
    return this->transaction->sourceAccount;
}

TransactionBuilder& TransactionBuilder::setTargetAccount(const keto::asn1::HashHelper& hashHelper) {
    this->transaction->targetAccount = (Hash_t)hashHelper;
    return (*this);
}


keto::asn1::HashHelper TransactionBuilder::getTargetAccount() {
    return this->transaction->targetAccount;
}

TransactionBuilder& TransactionBuilder::addAction(const std::shared_ptr<ActionBuilder> action) {
    if (0!= ASN_SEQUENCE_ADD(&this->transaction->actions,action->takePtr())) {
        BOOST_THROW_EXCEPTION(keto::chain_common::ActionSequenceAddFailedException());
    }
    return (*this);
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

void* TransactionBuilder::getPtr() {
    return this->transaction;
}

struct asn_TYPE_descriptor_s* TransactionBuilder::getType() {
    return &asn_DEF_Transaction;
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