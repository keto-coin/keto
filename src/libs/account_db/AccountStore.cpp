/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AccountStore.cpp
 * Author: ubuntu
 * 
 * Created on March 5, 2018, 6:02 AM
 */

#include <memory>
#include <string>
#include <vector>

#include "keto/crypto/Containers.hpp"
#include "keto/crypto/SecureVectorUtils.hpp"
#include "keto/rocks_db/SliceHelper.hpp"
#include "keto/account_db/Constants.hpp"
#include "keto/account_db/AccountStore.hpp"
#include "keto/account_db/AccountRDFStatement.hpp"
#include "keto/account_db/AccountRDFStatementBuilder.hpp"
#include "keto/account_db/AccountSystemOntologyTypes.hpp"
#include "keto/account_db/Exception.hpp"
#include "keto/asn1/RDFSubjectHelper.hpp"

namespace keto {
namespace account_db {

static std::shared_ptr<AccountStore> singleton;
    
AccountStore::AccountStore() {
    dbManagerPtr = std::shared_ptr<keto::rocks_db::DBManager>(
            new keto::rocks_db::DBManager(Constants::DB_LIST));
    accountGraphStoreManagerPtr = AccountGraphStoreManagerPtr(new AccountGraphStoreManager());
    accountResourceManagerPtr  =  AccountResourceManagerPtr(
            new AccountResourceManager(dbManagerPtr));

}

AccountStore::~AccountStore() {
    accountResourceManagerPtr.reset();
    accountGraphStoreManagerPtr.reset();
    dbManagerPtr.reset();
}

std::shared_ptr<AccountStore> AccountStore::init() {
    if (!singleton) {
        singleton = std::shared_ptr<AccountStore>(new AccountStore());
    }
    return singleton;
}

void AccountStore::fin() {
    singleton.reset();
}

std::shared_ptr<AccountStore> AccountStore::getInstance() {
    return singleton;
}

bool AccountStore::getAccountInfo(const keto::asn1::HashHelper& accountHash,
            keto::proto::AccountInfo& result) {
    AccountResourcePtr resource = accountResourceManagerPtr->getResource();
    rocksdb::Transaction* accountTransaction = resource->getTransaction(Constants::ACCOUNTS_MAPPING);
    keto::rocks_db::SliceHelper accountHashHelper(keto::crypto::SecureVectorUtils().copyFromSecure(
        accountHash));
    rocksdb::ReadOptions readOptions;
    std::string value;
    if (rocksdb::Status::OK() != accountTransaction->Get(readOptions,accountHashHelper,&value)) {
        return false;
    }
    result.ParseFromString(value);
    return true;
}

void AccountStore::applyTransaction(
        const keto::transaction_common::TransactionMessageHelperPtr& transactionMessageHelper) {
    keto::proto::AccountInfo accountInfo;
    AccountRDFStatementBuilderPtr accountRDFStatementBuilder(new AccountRDFStatementBuilder(
        transactionMessageHelper));
    bool existingAccount = true;
    if (!getAccountInfo(transactionMessageHelper->getTargetAccount(),accountInfo)) {
        existingAccount = false;
        std::cout << "The account has not been found [" << 
                transactionMessageHelper->getTargetAccount().getHash(keto::common::HEX) 
                << "][" << 
                transactionMessageHelper->getSourceAccount().getHash(keto::common::HEX)
                << "]" << std::endl;
    }
    
    for (AccountRDFStatementPtr accountRDFStatement : accountRDFStatementBuilder->getStatements()) {
        for (std::string subject : accountRDFStatement->getModel()->subjects()) {
            keto::asn1::RDFSubjectHelperPtr subjectPtr = 
                    accountRDFStatement->getModel()->operator [](subject);
            if (!AccountSystemOntologyTypes::validateClassOperation(
                transactionMessageHelper->getTargetAccount(),
                existingAccount,subjectPtr)) {
                BOOST_THROW_EXCEPTION(keto::account_db::InvalidAccountOperationException());
            }

                    std::cout << "The subject : " << subject << std::endl;
            std::cout << "The class : " << subjectPtr->getOntologyClass() << std::endl;
            for (std::string predicates : subjectPtr->listPredicates()) {
                std::cout << "The predicates : " << predicates << std::endl;
            }
        }
    }
}

}
}
