/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   KeystoreModule.cpp
 * Author: ubuntu
 * 
 * Created on January 20, 2018, 4:41 PM
 */

#include "keto/keystore/KeystoreModule.hpp"
#include "keto/common/MetaInfo.hpp"

namespace keto {
namespace keystore {


KeystoreModule::KeystoreModule() {
}

KeystoreModule::~KeystoreModule() {
}

// meta methods
const std::string KeystoreModule::getName() const {
    return "KeystoreModule";
}

const std::string KeystoreModule::getDescription() const {
    return "The Keystore Module responsible for managing keys in memory and disk.";
}

const std::string KeystoreModule::getVersion() const {
    return keto::common::MetaInfo::VERSION;
}

}
}