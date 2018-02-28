/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BlockResourceManager.cpp
 * Author: ubuntu
 * 
 * Created on February 28, 2018, 11:01 AM
 */

#include "keto/server_common/TransactionHelper.hpp"
#include "keto/block_db/BlockResourceManager.hpp"

namespace keto {
namespace block_db {

thread_local BlockResourcePtr BlockResourceManager::blockResourcePtr;

BlockResourceManager::BlockResourceManager(std::shared_ptr<DBManager> dbManagerPtr) :
    dbManagerPtr(dbManagerPtr) {
}

BlockResourceManager::~BlockResourceManager() {
}

void BlockResourceManager::commit() {
    if (blockResourcePtr) {
        blockResourcePtr->commit();
        blockResourcePtr.reset();
    }
}

void BlockResourceManager::rollback() {
    if (blockResourcePtr) {
        blockResourcePtr->rollback();
        blockResourcePtr.reset();
    }
}

BlockResourcePtr BlockResourceManager::getResource() {
    if (!blockResourcePtr) {
        blockResourcePtr = BlockResourcePtr(new BlockResource(dbManagerPtr));
        keto::server_common::enlistResource(*this);
    }
    return blockResourcePtr;
}


}
}
