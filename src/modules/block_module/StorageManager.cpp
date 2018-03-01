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

#include "keto/block/StorageManager.hpp"
#include "keto/block_db/BlockChainStore.hpp"

namespace keto {
namespace block {


static std::shared_ptr<StorageManager> singleton;


StorageManager::StorageManager() {
    keto::block_db::BlockChainStore::init();
}

StorageManager::~StorageManager() {
    keto::block_db::BlockChainStore::fin();
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