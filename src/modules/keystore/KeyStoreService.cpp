/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   KeyStoreService.cpp
 * Author: ubuntu
 * 
 * Created on February 17, 2018, 8:36 AM
 */

#include "keto/keystore/KeyStoreService.hpp"
#include "include/keto/keystore/KeyStoreService.hpp"
#include "include/keto/keystore/SessionKeyManager.hpp"

namespace keto {
namespace keystore {

static std::shared_ptr<KeyStoreService> singleton;
    
KeyStoreService::KeyStoreService() : 
    sessionKeyManager(new SessionKeyManager()) {
}

KeyStoreService::~KeyStoreService() {
}

std::shared_ptr<KeyStoreService> KeyStoreService::init() {
    if (!singleton) {
        singleton = std::shared_ptr<KeyStoreService>(new KeyStoreService());
    }
    return singleton;
}

void KeyStoreService::fin() {
    singleton.reset();
}

std::shared_ptr<KeyStoreService> KeyStoreService::getInstance() {
    return singleton;
}

std::shared_ptr<SessionKeyManager> KeyStoreService::getSessionKeyManager() {
    return this->sessionKeyManager;
}

}
}
