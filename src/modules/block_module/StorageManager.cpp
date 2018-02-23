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

#include <condition_variable>

#include "keto/block/StorageManager.hpp"
#include "include/keto/block/StorageManager.hpp"

namespace keto {
namespace block {


static std::shared_ptr<StorageManager> singleton;


StorageManager::StorageManager() {
}

StorageManager::~StorageManager() {
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