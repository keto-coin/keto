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

namespace keto {
namespace account_db {

AccountRDFStatementBuilder::AccountRDFStatementBuilder(
    const keto::transaction_common::TransactionMessageHelperPtr& transactionMessageHelper) :
    transactionMessageHelper(transactionMessageHelper) {
    for (int count = 0; count < 
            transactionMessageHelper->operator TransactionMessage_t&().changeSet.list.count; count++) {
        SignedChangeSet* signedChangeSet =
                transactionMessageHelper->operator TransactionMessage_t&().changeSet.list.array[count];
        for (int index = 0 ; index < signedChangeSet->changeSet.changes.list.count; index++) {
            statements.push_back(AccountRDFStatementPtr(new AccountRDFStatement(
                signedChangeSet->changeSet.changes.list.array[index])));
        }
    }
}

AccountRDFStatementBuilder::~AccountRDFStatementBuilder() {
    
}

std::vector<AccountRDFStatementPtr> AccountRDFStatementBuilder::getStatements() {
    return this->statements;
}


}
}
