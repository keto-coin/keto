/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AccountResourceManager.cpp
 * Author: ubuntu
 * 
 * Created on February 28, 2018, 11:01 AM
 */

#include "keto/server_common/TransactionHelper.hpp"
#include "keto/account_db/AccountResourceManager.hpp"

namespace keto {
namespace account_db {

thread_local AccountResourcePtr AccountResourceManager::accountResourcePtr;

AccountResourceManager::AccountResourceManager(
        std::shared_ptr<keto::rocks_db::DBManager> dbManagerPtr,
        const AccountGraphStoreManagerPtr& accountGraphStoreManagerPtr) :
    dbManagerPtr(dbManagerPtr), accountGraphStoreManagerPtr(accountGraphStoreManagerPtr) {
}

AccountResourceManager::~AccountResourceManager() {
}

void AccountResourceManager::commit() {
    if (accountResourcePtr) {
        accountResourcePtr->commit();
        accountResourcePtr.reset();
    }
}

void AccountResourceManager::rollback() {
    if (accountResourcePtr) {
        accountResourcePtr->rollback();
        accountResourcePtr.reset();
    }
}

AccountResourcePtr AccountResourceManager::getResource() {
    if (!accountResourcePtr) {
        accountResourcePtr = AccountResourcePtr(new AccountResource(dbManagerPtr,accountGraphStoreManagerPtr));
        keto::server_common::enlistResource(*this);
    }
    return accountResourcePtr;
}


}
}
