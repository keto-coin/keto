/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AccountResource.cpp
 * Author: ubuntu
 * 
 * Created on February 28, 2018, 10:56 AM
 */

#include <rocksdb/utilities/transaction.h>

#include "keto/account_db/AccountResource.hpp"

namespace keto {
namespace account_db {


AccountResource::AccountResource(std::shared_ptr<keto::rocks_db::DBManager> dbManagerPtr) : 
dbManagerPtr(dbManagerPtr) {
}

AccountResource::~AccountResource() {
    // rollback all changes as we can assume the resource is not getting cleared correctly
    for(std::map<std::string,rocksdb::Transaction*>::iterator iter = 
            transactionMap.begin(); iter != transactionMap.end(); iter++)
    {
        iter->second->Rollback();
        delete iter->second;
    }
    transactionMap.clear();
}

void AccountResource::commit() {
    for(std::map<std::string,rocksdb::Transaction*>::iterator iter = 
            transactionMap.begin(); iter != transactionMap.end(); iter++)
    {
        iter->second->Commit();
        delete iter->second;
    }
    transactionMap.clear();
}

void AccountResource::rollback() {
    // rollback all changes as we can assume the resource is not getting cleared correctly
    for(std::map<std::string,rocksdb::Transaction*>::iterator iter = 
            transactionMap.begin(); iter != transactionMap.end(); iter++)
    {
        iter->second->Rollback();
        delete iter->second;
    }
    transactionMap.clear();
}


rocksdb::Transaction* AccountResource::getTransaction(const std::string& name) {
    if (!transactionMap.count(name)) {
        keto::rocks_db::DBConnectorPtr dbConnectionPtr = 
                dbManagerPtr->getConnection(name);
        rocksdb::WriteOptions write_options;
        transactionMap[name] = dbConnectionPtr->getDB()->BeginTransaction(
                write_options);
        
    }
    return transactionMap[name];
}


}
}