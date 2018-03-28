/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AccountGraphStoreManager.cpp
 * Author: ubuntu
 * 
 * Created on March 20, 2018, 7:58 AM
 */

#include <sstream>

#include "keto/account_db/AccountGraphStoreManager.hpp"
#include "keto/account_db/Exception.hpp"
#include "keto/account_db/Constants.hpp"

namespace keto {
namespace account_db {


AccountGraphStoreManager::AccountGraphStoreManager() {
    // if the base graph exists load it otherwise assume it will not be
    // created until the genesis process is called
    if (AccountGraphStoreManager::checkForDb(Constants::BASE_GRAPH)) {
        this->graphs[Constants::BASE_GRAPH] = AccountGraphStorePtr(new AccountGraphStore(
                Constants::BASE_GRAPH));
    }
}

AccountGraphStoreManager::~AccountGraphStoreManager() {
}

AccountGraphStorePtr AccountGraphStoreManager::operator[](const std::string& dbName) {
    if (this->graphs.count(dbName)) {
        return this->graphs[dbName];
    }
    if (!AccountGraphStore::checkForDb(dbName)) {
        return AccountGraphStorePtr();
    }
    AccountGraphStorePtr result(new AccountGraphStore(dbName));
    this->graphs[Constants::BASE_GRAPH] = result;
    return result;
}

bool AccountGraphStoreManager::checkForDb(const std::string& dbName) {
    if (this->graphs.count(dbName)) {
        return true;
    }
    return AccountGraphStore::checkForDb(dbName);
}

AccountGraphStorePtr AccountGraphStoreManager::createStore(const std::string& dbName) {
    if (AccountGraphStore::checkForDb(dbName)) {
        std::stringstream ss;
        ss << "Graph db has been created by this name : " << dbName;
        BOOST_THROW_EXCEPTION(keto::account_db::DuplicateGraphDBException(
            ss.str()));
    }
    AccountGraphStorePtr result(new AccountGraphStore(dbName));
    this->graphs[Constants::BASE_GRAPH] = result;
    return result;
}


}
}