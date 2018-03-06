/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StorageManager.cpp
 * Author: ubuntu
 * 
 * Created on March 6, 2018, 6:13 AM
 */

#include "keto/router/StorageManager.hpp"
#include "keto/router_db/RouterStore.hpp"


namespace keto {
namespace router {

static std::shared_ptr<StorageManager> singleton;
    
StorageManager::StorageManager() {
    keto::router_db::RouterStore::init();
}

StorageManager::~StorageManager() {
    keto::router_db::RouterStore::fin();
}


std::shared_ptr<StorageManager> StorageManager::init() {
    if (!singleton) {
        singleton = std::shared_ptr<StorageManager>(new StorageManager());
    }
    return singleton;
}

void StorageManager::fin() {
    singleton.reset();
}

std::shared_ptr<StorageManager> StorageManager::getInstance() {
    return singleton;
}


}
}
