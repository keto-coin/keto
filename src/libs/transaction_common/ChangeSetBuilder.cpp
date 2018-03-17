/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ChangeSetBuilder.cpp
 * Author: ubuntu
 * 
 * Created on March 17, 2018, 3:51 AM
 */

#include "ChangeData.h"

#include "keto/transaction_common/Exception.hpp"

#include "keto/transaction_common/ChangeSetBuilder.hpp"

#include "keto/common/MetaInfo.hpp"


namespace keto {
namespace transaction_common {


ChangeSetBuilder::ChangeSetBuilder() {
    this->changeSet = (ChangeSet_t*)calloc(1, sizeof *changeSet);
    this->changeSet->version = keto::common::MetaInfo::PROTOCOL_VERSION;
    
}

ChangeSetBuilder::ChangeSetBuilder(const keto::asn1::HashHelper& transactionHash, 
        const keto::asn1::HashHelper& accountHash) {
    this->changeSet = (ChangeSet_t*)calloc(1, sizeof *changeSet);
    this->changeSet->version = keto::common::MetaInfo::PROTOCOL_VERSION;
    this->changeSet->transactionHash = transactionHash;
    this->changeSet->accountHash = accountHash;
    
}

ChangeSetBuilder::~ChangeSetBuilder() {
    if (changeSet) {
        ASN_STRUCT_FREE(asn_DEF_ChangeSet, changeSet);
        changeSet = NULL;
    }
}


ChangeSetBuilder& ChangeSetBuilder::setTransaction(
        const keto::asn1::HashHelper& transactionHash) {
    this->changeSet->transactionHash = transactionHash;
    return (*this);
}

ChangeSetBuilder& ChangeSetBuilder::setAccount(
        const keto::asn1::HashHelper& accountHash){
    this->changeSet->accountHash = accountHash;
    return (*this);
}

ChangeSetBuilder& ChangeSetBuilder::setStatus(const Status& status) {
    this->changeSet->status = status;
    return (*this);
}


ChangeSetBuilder& ChangeSetBuilder::addChange(ANY_t* asn1Change) {
    ChangeData_t* changeData = (ChangeData_t*)calloc(1, sizeof *changeData);
    changeData->present = ChangeData_PR_asn1Change;
    changeData->choice.asn1Change = *asn1Change;
    free(asn1Change);
    if (0!= ASN_SEQUENCE_ADD(&this->changeSet->changes,changeData)) {
        BOOST_THROW_EXCEPTION(keto::transaction_common::ChangeSequenceAddFailedException());
    }
    return (*this);
}

ChangeSetBuilder::operator ChangeSet_t*() {
    ChangeSet_t* result = this->changeSet;
    this->changeSet = 0;
    return result;
}

ChangeSetBuilder::operator ChangeSet_t&() {
    return *this->changeSet;
}

}
}