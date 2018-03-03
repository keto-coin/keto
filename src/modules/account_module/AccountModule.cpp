/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AccountModule.cpp
 * Author: ubuntu
 * 
 * Created on March 3, 2018, 11:53 AM
 */

#include "keto/account/AccountModule.hpp"

namespace keto {
namespace account {


AccountModule::AccountModule() {
}

AccountModule::~AccountModule() {
}

// meta methods
const std::string AccountModule::getName() const {
    return "AccountModule";
}

const std::string AccountModule::getDescription() const {
    return "The Account Module responsible for managing the accounts.";
}

const std::string AccountModule::getVersion() const {
    return keto::common::MetaInfo::VERSION;
}


}
}