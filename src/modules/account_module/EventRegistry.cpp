/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EventRegistry.cpp
 * Author: ubuntu
 * 
 * Created on March 6, 2018, 1:42 PM
 */

#include "keto/account/EventRegistry.hpp"

#include "keto/server_common/Events.hpp"
#include "keto/server_common/EventServiceHelpers.hpp"


#include "keto/account/AccountService.hpp"
#include "include/keto/account/AccountService.hpp"

namespace keto {
namespace account {

EventRegistry::EventRegistry() {
}

EventRegistry::~EventRegistry() {
}

keto::event::Event EventRegistry::checkAccount(const keto::event::Event& event) {
    return AccountService::getInstance()->checkAccount(event);
}

keto::event::Event EventRegistry::applyTransaction(const keto::event::Event& event) {
    return AccountService::getInstance()->applyTransaction(event);
}

void EventRegistry::registerEventHandlers() {
    keto::server_common::registerEventHandler (
            keto::server_common::Events::CHECK_ACCOUNT_MESSAGE,
            &keto::account::EventRegistry::checkAccount);
    keto::server_common::registerEventHandler (
            keto::server_common::Events::APPLY_ACCOUNT_TRANSACTION_MESSAGE,
            &keto::account::EventRegistry::applyTransaction);
}

void EventRegistry::deregisterEventHandlers() {
    keto::server_common::deregisterEventHandler(
            keto::server_common::Events::APPLY_ACCOUNT_TRANSACTION_MESSAGE);
    keto::server_common::deregisterEventHandler(
            keto::server_common::Events::CHECK_ACCOUNT_MESSAGE);
}


}
}