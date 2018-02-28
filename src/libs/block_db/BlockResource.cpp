/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BlockResource.cpp
 * Author: ubuntu
 * 
 * Created on February 28, 2018, 10:56 AM
 */

#include <rocksdb/utilities/transaction.h>

#include "keto/block_db/BlockResource.hpp"
#include "include/keto/block_db/DBManager.hpp"

namespace keto {
namespace block_db {


BlockResource::BlockResource(std::shared_ptr<DBManager> dbManagerPtr) : 
dbManagerPtr(dbManagerPtr) {
}

BlockResource::~BlockResource() {
    // rollback all changes as we can assume the resource is not getting cleared correctly
    for(std::map<std::string,rocksdb::Transaction*>::iterator iter = 
            transactionMap.begin(); iter != transactionMap.end(); iter++)
    {
        iter->second->Rollback();
        delete iter->second;
    }
    transactionMap.clear();
}

void BlockResource::commit() {
    for(std::map<std::string,rocksdb::Transaction*>::iterator iter = 
            transactionMap.begin(); iter != transactionMap.end(); iter++)
    {
        iter->second->Commit();
        delete iter->second;
    }
    transactionMap.clear();
}

void BlockResource::rollback() {
    // rollback all changes as we can assume the resource is not getting cleared correctly
    for(std::map<std::string,rocksdb::Transaction*>::iterator iter = 
            transactionMap.begin(); iter != transactionMap.end(); iter++)
    {
        iter->second->Rollback();
        delete iter->second;
    }
    transactionMap.clear();
}


rocksdb::Transaction* BlockResource::getTransaction(const std::string& name) {
    if (!transactionMap.count(name)) {
        keto::block_db::DBConnectorPtr dbConnectionPtr = 
                dbManagerPtr->getConnection(name);
        rocksdb::WriteOptions write_options;
        transactionMap[name] = dbConnectionPtr->getDB()->BeginTransaction(
                write_options);
        
    }
    return transactionMap[name];
}


}
}