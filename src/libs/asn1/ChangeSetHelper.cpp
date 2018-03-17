/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ChangeSetHelper.cpp
 * Author: ubuntu
 * 
 * Created on March 13, 2018, 10:54 AM
 */

#include "ChangeData.h"

#include "keto/asn1/ChangeSetHelper.hpp"
#include "keto/asn1/Exception.hpp"
#include "keto/common/MetaInfo.hpp"

namespace keto {
namespace asn1 {


ChangeSetHelper::ChangeSetHelper() {
}

ChangeSetHelper::ChangeSetHelper(const HashHelper& transactionHash,
        const HashHelper& accountHash) : transactionHash(transactionHash),
    accountHash(accountHash) {
    
}

ChangeSetHelper::~ChangeSetHelper() {
}

ChangeSetHelper& ChangeSetHelper::setTransactionHash(const HashHelper& transactionHash) {
    this->transactionHash = transactionHash;
    return (*this);
}

ChangeSetHelper& ChangeSetHelper::setAccountHash(const HashHelper& accountHash) {
    this->accountHash = accountHash;
    return (*this);
}

ChangeSetHelper& ChangeSetHelper::setStatus(const Status_t status) {
    this->status = status;
    return (*this);
}

ChangeSetHelper& ChangeSetHelper::addChange(const ANY_t& change) {
    this->changes.push_back(change);
    return (*this);
}

ChangeSetHelper::operator ChangeSet_t*() {
    ChangeSet_t* changeSet = (ChangeSet_t*)calloc(1, sizeof *changeSet);
    changeSet->version = keto::common::MetaInfo::PROTOCOL_VERSION;
    changeSet->transactionHash = this->transactionHash;
    changeSet->accountHash = this->accountHash;
    changeSet->status = this->status;
    
    for (ANY_t change : this->changes) {
        // check if the 
        ChangeData_t* changeData = (ChangeData_t*)calloc(1, sizeof *changeSet);
        changeData->choice.asn1Change = change;
        changeData->present = ChangeData_PR_asn1Change;
        if (0!= ASN_SEQUENCE_ADD(&changeSet->changes,new ANY_t(change))) {
            ASN_STRUCT_FREE(asn_DEF_ChangeSet, changeSet);
            BOOST_THROW_EXCEPTION(keto::asn1::FailedToAddChangeToChangeSetException());
        }
    }
    return changeSet;
}

ChangeSetHelper::operator ANY_t*() {
    ChangeSet_t* ptr = this->operator ChangeSet_t*();
    ANY_t* anyPtr = ANY_new_fromType(&asn_DEF_ChangeSet, ptr);
    ASN_STRUCT_FREE(asn_DEF_ChangeSet, ptr);
    if (!anyPtr) {
        BOOST_THROW_EXCEPTION(keto::asn1::TypeToAnyConversionFailedException());
    }
    return anyPtr;
}



}
}