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
#include <sstream>

#include "Account.pb.h"

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
#include "include/keto/account_db/AccountRDFStatement.hpp"
#include "include/keto/account_db/AccountGraphSession.hpp"

namespace keto {
namespace account_db {

static std::shared_ptr<AccountStore> singleton;
    
AccountStore::AccountStore() {
    dbManagerPtr = std::shared_ptr<keto::rocks_db::DBManager>(
            new keto::rocks_db::DBManager(Constants::DB_LIST));
    accountGraphStoreManagerPtr = AccountGraphStoreManagerPtr(new AccountGraphStoreManager());
    accountResourceManagerPtr  =  AccountResourceManagerPtr(
            new AccountResourceManager(dbManagerPtr,accountGraphStoreManagerPtr));

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
    AccountResourcePtr resource = accountResourceManagerPtr->getResource();
    keto::proto::AccountInfo accountInfo;
    AccountRDFStatementBuilderPtr accountRDFStatementBuilder;
    if (!getAccountInfo(transactionMessageHelper->getTargetAccount(),accountInfo)) {
        accountRDFStatementBuilder =  AccountRDFStatementBuilderPtr(
                new AccountRDFStatementBuilder(
                transactionMessageHelper,false));
        createAccount(transactionMessageHelper,accountRDFStatementBuilder,accountInfo);
    } else {
        accountRDFStatementBuilder =  AccountRDFStatementBuilderPtr(
                new AccountRDFStatementBuilder(
                transactionMessageHelper,true));
    }
    AccountGraphSessionPtr sessionPtr = resource->getGraphSession(accountInfo.graph_name());
        
    
    for (AccountRDFStatementPtr accountRDFStatement : accountRDFStatementBuilder->getStatements()) {
        keto::asn1::RDFModelHelperPtr rdfModel = accountRDFStatement->getModel();
        for (keto::asn1::RDFSubjectHelperPtr rdfSubject : rdfModel->getSubjects()) {
            if (accountRDFStatement->getOperation() == PERSIST) {
                sessionPtr->persist(rdfSubject);
            } else {
                sessionPtr->remove(rdfSubject);
            }
        }
    }
}

void AccountStore::sparqlQuery(
        const keto::proto::AccountInfo& accountInfo,
        keto::proto::SparqlQuery& sparlQuery) {
    AccountResourcePtr resource = accountResourceManagerPtr->getResource();
    AccountGraphSessionPtr sessionPtr = resource->getGraphSession(accountInfo.graph_name());
    sparlQuery.set_result(sessionPtr->query(sparlQuery.query()));
}

void AccountStore::createAccount(
            const keto::transaction_common::TransactionMessageHelperPtr& transactionMessageHelper,
            AccountRDFStatementBuilderPtr accountRDFStatementBuilder,
            keto::proto::AccountInfo& accountInfo) {
    if (accountRDFStatementBuilder->accountAction().compare(
                AccountSystemOntologyTypes::ACCOUNT_CREATE_OBJECT_STATUS)) {
        std::stringstream ss;
        ss << "The account does not exist [" << 
                transactionMessageHelper->getTargetAccount().getHash(keto::common::HEX) << "]";
        BOOST_THROW_EXCEPTION(keto::account_db::InvalidAccountOperationException(
                ss.str()));
    }
    accountInfo = accountRDFStatementBuilder->getAccountInfo();

    if (accountInfo.account_type().compare(AccountSystemOntologyTypes::ACCOUNT_TYPE::MASTER) ==0) {
        // We assume that the top most master account will not have a parent
        // we thus assume this will be during the genesis process and we set it to the base graph
        // for all future masters we set it to the hex hash value for the master account hash.
        if (accountInfo.parent_account_hash().empty()) {
            accountInfo.set_graph_name(Constants::BASE_GRAPH);
        } else {
            accountInfo.set_graph_name(transactionMessageHelper->getTargetAccount().getHash(keto::common::HEX));
        }
        if (!this->accountGraphStoreManagerPtr->checkForDb(accountInfo.graph_name())) {
            this->accountGraphStoreManagerPtr->createStore(accountInfo.graph_name());
        }
    } else {
        keto::asn1::HashHelper parentAccountHash(
                    accountInfo.parent_account_hash());
        keto::proto::AccountInfo parentAccountInfo;
        if (!getAccountInfo(parentAccountHash,parentAccountInfo)) {
            std::stringstream ss;
            ss << "The parent account [" << parentAccountHash.getHash(keto::common::HEX) << 
                    "] was not found for the account [" << 
                    transactionMessageHelper->getTargetAccount().getHash(keto::common::HEX) << "]["
                    << accountInfo.account_type() << "]";
            BOOST_THROW_EXCEPTION(keto::account_db::InvalidParentAccountException(
                    ss.str()));
        }
        accountInfo.set_graph_name(parentAccountInfo.graph_name());
    }
    setAccountInfo(transactionMessageHelper->getTargetAccount(),accountInfo);
}

void AccountStore::setAccountInfo(const keto::asn1::HashHelper& accountHash,
            keto::proto::AccountInfo& accountInfo) {
    AccountResourcePtr resource = accountResourceManagerPtr->getResource();
    rocksdb::Transaction* accountTransaction = resource->getTransaction(Constants::ACCOUNTS_MAPPING);
    keto::rocks_db::SliceHelper accountHashHelper(keto::crypto::SecureVectorUtils().copyFromSecure(
        accountHash));
    std::string pbValue;
    accountInfo.SerializeToString(&pbValue);
    keto::rocks_db::SliceHelper valueHelper(pbValue);
    accountTransaction->Put(accountHashHelper,valueHelper);
}




}
}
