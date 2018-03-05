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

#include "keto/account_db/Constants.hpp"
#include "keto/account_db/AccountStore.hpp"

namespace keto {
namespace account_db {

static std::shared_ptr<AccountStore> singleton;
    
AccountStore::AccountStore() {
    dbManagerPtr = std::shared_ptr<keto::rocks_db::DBManager>(
            new keto::rocks_db::DBManager(Constants::DB_LIST));
    accountResourceManagerPtr  =  AccountResourceManagerPtr(
            new AccountResourceManager(dbManagerPtr));

}

AccountStore::~AccountStore() {
    accountResourceManagerPtr.reset();
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


}
}
