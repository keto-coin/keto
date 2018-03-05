/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RouterResourceManager.cpp
 * Author: ubuntu
 * 
 * Created on February 28, 2018, 11:01 AM
 */

#include "keto/server_common/TransactionHelper.hpp"
#include "keto/router_db/RouterResourceManager.hpp"

namespace keto {
namespace router_db {

thread_local RouterResourcePtr RouterResourceManager::blockResourcePtr;

RouterResourceManager::RouterResourceManager(
    std::shared_ptr<keto::rocks_db::DBManager> dbManagerPtr) :
    dbManagerPtr(dbManagerPtr) {
}

RouterResourceManager::~RouterResourceManager() {
}

void RouterResourceManager::commit() {
    if (blockResourcePtr) {
        blockResourcePtr->commit();
        blockResourcePtr.reset();
    }
}

void RouterResourceManager::rollback() {
    if (blockResourcePtr) {
        blockResourcePtr->rollback();
        blockResourcePtr.reset();
    }
}

RouterResourcePtr RouterResourceManager::getResource() {
    if (!blockResourcePtr) {
        blockResourcePtr = RouterResourcePtr(new RouterResource(dbManagerPtr));
        keto::server_common::enlistResource(*this);
    }
    return blockResourcePtr;
}


}
}
