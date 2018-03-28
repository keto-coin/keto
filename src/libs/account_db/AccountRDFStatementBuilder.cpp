/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AccountStatementBuilder.cpp
 * Author: ubuntu
 * 
 * Created on March 20, 2018, 11:54 AM
 */

#include <vector>

#include "TransactionMessage.h"

#include "keto/account_db/AccountRDFStatementBuilder.hpp"
#include "include/keto/account_db/AccountRDFStatementBuilder.hpp"
#include "keto/account_db/Exception.hpp"
#include "keto/common/MetaInfo.hpp"
#include "include/keto/account_db/AccountSystemOntologyTypes.hpp"
#include "keto/crypto/SecureVectorUtils.hpp"

namespace keto {
namespace account_db {

AccountRDFStatementBuilder::AccountRDFStatementBuilder(
    const keto::transaction_common::TransactionMessageHelperPtr& transactionMessageHelper,
    bool existingAccount) :
    transactionMessageHelper(transactionMessageHelper) {
    this->accountInfo.set_version(keto::common::MetaInfo::PROTOCOL_VERSION);
    
    for (int count = 0; count < 
            transactionMessageHelper->operator TransactionMessage_t&().changeSet.list.count; count++) {
        SignedChangeSet* signedChangeSet =
                transactionMessageHelper->operator TransactionMessage_t&().changeSet.list.array[count];
        for (int index = 0 ; index < signedChangeSet->changeSet.changes.list.count; index++) {
            AccountRDFStatementPtr accountRDFStatement(new AccountRDFStatement(
                signedChangeSet->changeSet.changes.list.array[index]));
            
            for (std::string subject : accountRDFStatement->getModel()->subjects()) {
                keto::asn1::RDFSubjectHelperPtr subjectPtr = 
                        accountRDFStatement->getModel()->operator [](subject);
                if (!AccountSystemOntologyTypes::validateClassOperation(
                    transactionMessageHelper->getTargetAccount(),
                        existingAccount,subjectPtr)) {
                    BOOST_THROW_EXCEPTION(keto::account_db::InvalidAccountOperationException());
                }
                if (AccountSystemOntologyTypes::isAccountOntologyClass(subjectPtr)) {
                    this->action = 
                            (*subjectPtr)[AccountSystemOntologyTypes::ACCOUNT_PREDICATES::STATUS]->getStringLiteral();
                    
                    // setup the account hash
                    keto::asn1::HashHelper accountHash(
                            (*subjectPtr)[AccountSystemOntologyTypes::ACCOUNT_PREDICATES::ID]->getStringLiteral(),
                            keto::common::HEX);
                    accountInfo.set_account_hash(
                        keto::crypto::SecureVectorUtils().copySecureToString(
                        accountHash));
                    
                    if (subjectPtr->containsPredicate(AccountSystemOntologyTypes::ACCOUNT_PREDICATES::PARENT)) {
                        keto::asn1::HashHelper parentAccountHash(
                            (*subjectPtr)[AccountSystemOntologyTypes::ACCOUNT_PREDICATES::PARENT]->getStringLiteral(),
                                keto::common::HEX);
                        accountInfo.set_parent_account_hash(
                            keto::crypto::SecureVectorUtils().copySecureToString(
                            parentAccountHash));
                    }
                    accountInfo.set_account_type(
                        (*subjectPtr)[AccountSystemOntologyTypes::ACCOUNT_PREDICATES::TYPE]->getStringLiteral());
                    
                }
            }
            statements.push_back(accountRDFStatement);
            
        }
    }
}

AccountRDFStatementBuilder::~AccountRDFStatementBuilder() {
    
}

std::vector<AccountRDFStatementPtr> AccountRDFStatementBuilder::getStatements() {
    return this->statements;
}

keto::proto::AccountInfo AccountRDFStatementBuilder::getAccountInfo() {
    return accountInfo;
}

std::string AccountRDFStatementBuilder::accountAction() {
    return this->action;
}
    


}
}
