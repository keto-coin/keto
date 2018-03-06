/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RouterStore.cpp
 * Author: ubuntu
 * 
 * Created on March 6, 2018, 3:20 AM
 */

#include <rocksdb/utilities/transaction.h>
#include <google/protobuf/message_lite.h>

#include "keto/router_db/RouterStore.hpp"
#include "keto/router_db/Constants.hpp"

#include "keto/crypto/SecureVectorUtils.hpp"
#include "keto/rocks_db/SliceHelper.hpp"


namespace keto {
namespace router_db {

static std::shared_ptr<RouterStore> singleton;
    
RouterStore::RouterStore() {
    dbManagerPtr = std::shared_ptr<keto::rocks_db::DBManager>(
            new keto::rocks_db::DBManager(Constants::DB_LIST));
    routerResourceManagerPtr  =  RouterResourceManagerPtr(
            new RouterResourceManager(dbManagerPtr));
}

RouterStore::~RouterStore() {
    routerResourceManagerPtr.reset();
    dbManagerPtr.reset();
}

std::shared_ptr<RouterStore> RouterStore::init() {
    if (singleton) {
        return singleton;
    }
    return singleton = std::shared_ptr<RouterStore>(new RouterStore());
}

void RouterStore::fin() {
    singleton.reset();
}

std::shared_ptr<RouterStore> RouterStore::getInstance() {
    return singleton;
}

bool RouterStore::getAccountRouting(
            const keto::asn1::HashHelper& accountHash,
            keto::proto::AccountRoutingStore& result) {
    RouterResourcePtr resource = routerResourceManagerPtr->getResource();
    rocksdb::Transaction* routerTransaction = resource->getTransaction(Constants::ROUTER_INDEX);
    keto::rocks_db::SliceHelper accountHashHelper(keto::crypto::SecureVectorUtils().copyFromSecure(
        accountHash));
    rocksdb::ReadOptions readOptions;
    std::string value;
    if (rocksdb::Status::OK() != routerTransaction->Get(readOptions,accountHashHelper,&value)) {
        return false;
    }
    result.ParseFromString(value);
    return true;
}

void RouterStore::setAccountRouting(
            const keto::asn1::HashHelper& accountHash,
            const keto::proto::AccountRoutingStore& routing) {
    RouterResourcePtr resource = routerResourceManagerPtr->getResource();
    rocksdb::Transaction* routerTransaction = resource->getTransaction(Constants::ROUTER_INDEX);
    keto::rocks_db::SliceHelper accountHashHelper(keto::crypto::SecureVectorUtils().copyFromSecure(
        accountHash));
    keto::rocks_db::SliceHelper value(routing.SerializePartialAsString());
    routerTransaction->Put(accountHashHelper,value);
}

}
}
