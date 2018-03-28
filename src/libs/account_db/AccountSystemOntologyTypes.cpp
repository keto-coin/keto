/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AccountSystemOntologyTypes.cpp
 * Author: ubuntu
 * 
 * Created on March 26, 2018, 2:59 AM
 */

#include <algorithm>

#include "keto/account_db/AccountSystemOntologyTypes.hpp"
#include "include/keto/account_db/AccountSystemOntologyTypes.hpp"

namespace keto {
namespace account_db {


const char* AccountSystemOntologyTypes::ACCOUNT_ONTOLOGY_CLASS = "http://keto-coin.io/schema/rdf/1.0/keto/Account#Account";

const char* AccountSystemOntologyTypes::ACCOUNT_PREDICATES::STATUS = "http://keto-coin.io/schema/rdf/1.0/keto/Account#status";
const char* AccountSystemOntologyTypes::ACCOUNT_PREDICATES::ID = "http://keto-coin.io/schema/rdf/1.0/keto/Account#id";
const char* AccountSystemOntologyTypes::ACCOUNT_PREDICATES::PARENT = "http://keto-coin.io/schema/rdf/1.0/keto/Account#parent";
const char* AccountSystemOntologyTypes::ACCOUNT_PREDICATES::TYPE = "http://keto-coin.io/schema/rdf/1.0/keto/Account#type";

const char* AccountSystemOntologyTypes::ACCOUNT_CREATE_OBJECT_STATUS = "create";

const char* AccountSystemOntologyTypes::ACCOUNT_TYPE::MASTER        = "master";
const char* AccountSystemOntologyTypes::ACCOUNT_TYPE::ROOT          = "root";
const char* AccountSystemOntologyTypes::ACCOUNT_TYPE::SYSTEM        = "system";
const char* AccountSystemOntologyTypes::ACCOUNT_TYPE::PROXY         = "proxy";
const char* AccountSystemOntologyTypes::ACCOUNT_TYPE::STANDARD      = "standard";
const char* AccountSystemOntologyTypes::ACCOUNT_TYPE::SLAVE         = "slave";


const std::vector<std::string> AccountSystemOntologyTypes::ONTOLOGY_CLASSES = {
    AccountSystemOntologyTypes::ACCOUNT_ONTOLOGY_CLASS
    }; 


bool objectEqual(const std::vector<keto::asn1::RDFObjectHelperPtr>& objectHelpers,
        const std::string& value) {
    for (const keto::asn1::RDFObjectHelperPtr& objectHelper : objectHelpers) {
        if (objectHelper->getValue().compare(value) == 0) {
            return true;
        }
    }
    return false;
}

bool AccountSystemOntologyTypes::validateClassOperation(
    const keto::asn1::HashHelper& targetAccount,
    const bool existingAccount,
    const keto::asn1::RDFSubjectHelperPtr& rdfSubjectHelperPtr) {
    
    
    auto iter = 
            std::find(AccountSystemOntologyTypes::ONTOLOGY_CLASSES.begin(), 
            AccountSystemOntologyTypes::ONTOLOGY_CLASSES.end(),
            rdfSubjectHelperPtr->getOntologyClass());
    if (iter == AccountSystemOntologyTypes::ONTOLOGY_CLASSES.end()) {
        return true;
    }
    
    // at present 
    if (rdfSubjectHelperPtr->getOntologyClass().compare(AccountSystemOntologyTypes::ACCOUNT_ONTOLOGY_CLASS) == 0) {
        if (!existingAccount && (!objectEqual((*rdfSubjectHelperPtr)[ACCOUNT_PREDICATES::STATUS]->listObjects(),
            AccountSystemOntologyTypes::ACCOUNT_CREATE_OBJECT_STATUS) ||
            !objectEqual((*rdfSubjectHelperPtr)[ACCOUNT_PREDICATES::ID]->listObjects(),
            targetAccount.getHash(keto::common::HEX)))) {
            return false;
        }
    }
    
    return true;
}


bool AccountSystemOntologyTypes::isAccountOntologyClass(
        const keto::asn1::RDFSubjectHelperPtr& rdfSubjectHelperPtr) {
    if (rdfSubjectHelperPtr->getOntologyClass().compare(
            AccountSystemOntologyTypes::ACCOUNT_ONTOLOGY_CLASS) == 0) {
       return true; 
    }
    return false;
}


}
}