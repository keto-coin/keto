/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StorageManager.cpp
 * Author: ubuntu
 * 
 * Created on February 21, 2018, 9:03 AM
 */

#include <string>
#include <iostream>
#include <condition_variable>

#include "keto/account/StorageManager.hpp"
#include "keto/account_db/AccountStore.hpp"

namespace keto {
namespace account {


static std::shared_ptr<StorageManager> singleton;


StorageManager::StorageManager() {
    keto::account_db::AccountStore::init();
}

StorageManager::~StorageManager() {
    keto::account_db::AccountStore::fin();
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