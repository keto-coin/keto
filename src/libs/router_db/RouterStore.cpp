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

#include "keto/router_db/RouterStore.hpp"
#include "keto/router_db/Constants.hpp"

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


}
}
