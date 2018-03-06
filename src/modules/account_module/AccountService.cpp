/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AccountService.cpp
 * Author: ubuntu
 * 
 * Created on March 6, 2018, 1:41 PM
 */

#include <string>
#include <iostream>

#include "Account.pb.h"

#include "keto/server_common/EventServiceHelpers.hpp"
#include "keto/account/AccountService.hpp"

namespace keto {
namespace account {

static std::shared_ptr<AccountService> singleton;

AccountService::AccountService() {
}

AccountService::~AccountService() {
}

// account service management methods
std::shared_ptr<AccountService> AccountService::init() {
    if (!singleton) {
        singleton = std::shared_ptr<AccountService>(new AccountService());
    }
    return singleton;
}

void AccountService::fin() {
    singleton.reset();
}

std::shared_ptr<AccountService> AccountService::getInstance() {
    return singleton;
}

// account methods
keto::event::Event AccountService::checkAccount(const keto::event::Event& event) {
    keto::proto::CheckForAccount  messageWrapper = 
            keto::server_common::fromEvent<keto::proto::CheckForAccount>(event);
    
    
    return keto::server_common::toEvent<keto::proto::CheckForAccount>(messageWrapper);
}


}
}