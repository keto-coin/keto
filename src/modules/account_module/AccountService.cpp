/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AccountService.cpp
 * Author: ubuntu
 * 
 * Created on March 6, 2018, 1:41 PM
 */

#include <string>
#include <iostream>

#include "Account.pb.h"
#include "BlockChain.pb.h"
#include "Sparql.pb.h"
#include "Contract.pb.h"


#include "keto/asn1/HashHelper.hpp"
#include "keto/asn1/ContractHelper.hpp"
#include "keto/server_common/EventServiceHelpers.hpp"
#include "keto/account/AccountService.hpp"
#include "keto/account_db/AccountStore.hpp"
#include "keto/transaction_common/TransactionProtoHelper.hpp"


namespace keto {
namespace account {

static std::shared_ptr<AccountService> singleton;

AccountService::AccountService() {
}

AccountService::~AccountService() {
}

// account service management methods
std::shared_ptr<AccountService> AccountService::init() {
    if (!singleton) {
        singleton = std::shared_ptr<AccountService>(new AccountService());
    }
    return singleton;
}

void AccountService::fin() {
    singleton.reset();
}

std::shared_ptr<AccountService> AccountService::getInstance() {
    return singleton;
}

keto::event::Event AccountService::applyTransaction(const keto::event::Event& event) {
    keto::proto::Transaction  transaction = 
            keto::server_common::fromEvent<keto::proto::Transaction>(event);
    
    keto::transaction_common::TransactionProtoHelper transactionProtoHelper;
    transactionProtoHelper = transaction;
    keto::account_db::AccountStore::getInstance()->applyTransaction(
        transactionProtoHelper.getTransactionMessageHelper());
    
    return keto::server_common::toEvent<keto::proto::Transaction>(transaction);
}
    

// account methods
keto::event::Event AccountService::checkAccount(const keto::event::Event& event) {
    keto::proto::CheckForAccount  checkForAccount = 
            keto::server_common::fromEvent<keto::proto::CheckForAccount>(event);
    
    keto::proto::AccountInfo accountInfo;
    keto::asn1::HashHelper accountHashHelper(checkForAccount.account_hash());
    if (keto::account_db::AccountStore::getInstance()->getAccountInfo(accountHashHelper,
            accountInfo)) {
        checkForAccount.set_found(true);
    } else {
        checkForAccount.set_found(false);
    }
    
    return keto::server_common::toEvent<keto::proto::CheckForAccount>(checkForAccount);
}

keto::event::Event AccountService::sparqlQuery(const keto::event::Event& event) {
    keto::proto::SparqlQuery  sparqlQuery = 
            keto::server_common::fromEvent<keto::proto::SparqlQuery>(event);
    
    keto::proto::AccountInfo accountInfo;
    keto::asn1::HashHelper accountHashHelper(sparqlQuery.account_hash());
    if (keto::account_db::AccountStore::getInstance()->getAccountInfo(accountHashHelper,
            accountInfo)) {
        keto::account_db::AccountStore::getInstance()->sparqlQuery(accountInfo,sparqlQuery);
    }
    
    return keto::server_common::toEvent<keto::proto::SparqlQuery>(sparqlQuery);
}

keto::event::Event AccountService::getContract(const keto::event::Event& event) {
    keto::proto::ContractMessage  contractMessage = 
            keto::server_common::fromEvent<keto::proto::ContractMessage>(event);
    keto::proto::AccountInfo accountInfo;
    keto::asn1::HashHelper accountHashHelper(contractMessage.account_hash());
    if (keto::account_db::AccountStore::getInstance()->getAccountInfo(accountHashHelper,
            accountInfo)) {
        keto::account_db::AccountStore::getInstance()->getContract(accountInfo,contractMessage);
    }
    
    return keto::server_common::toEvent<keto::proto::ContractMessage>(contractMessage);
}

}
}