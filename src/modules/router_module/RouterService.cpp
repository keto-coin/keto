/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RouterService.cpp
 * Author: ubuntu
 * 
 * Created on March 2, 2018, 4:04 PM
 */

#include <iostream>

#include "keto/router/RouterService.hpp"
#include "keto/server_common/Events.hpp"
#include "keto/server_common/EventServiceHelpers.hpp"
#include "keto/router_db/RouterStore.hpp"

#include "Protocol.pb.h"
#include "Account.pb.h"

namespace keto {
namespace router {

static std::shared_ptr<RouterService> singleton;

RouterService::RouterService() {
}

RouterService::~RouterService() {
}

std::shared_ptr<RouterService> RouterService::init() {
    if (!singleton) {
        singleton = std::shared_ptr<RouterService>(new RouterService());
    }
    return singleton;
}

void RouterService::fin() {
    singleton.reset();
}

std::shared_ptr<RouterService> RouterService::getInstance() {
    return singleton;
}


keto::event::Event RouterService::routeMessage(const keto::event::Event& event) {
    keto::proto::MessageWrapper  messageWrapper = 
            keto::server_common::fromEvent<keto::proto::MessageWrapper>(event);
    
    keto::asn1::HashHelper accountHash(messageWrapper.account_hash());
    keto::proto::AccountRoutingStore accountRouting;
    if (keto::router_db::RouterStore::getInstance()->getAccountRouting(
            accountHash,accountRouting)) {
        
        // route
        keto::proto::MessageWrapperResponse response;
        response.set_success(true);
        response.set_result("routed");
        return keto::server_common::toEvent<keto::proto::MessageWrapperResponse>(response);
    }
    
    keto::proto::CheckForAccount checkForAccount;
    checkForAccount.set_version(1);
    checkForAccount.set_account_hash(messageWrapper.account_hash());
    checkForAccount.set_found(false);
    
    checkForAccount = 
            keto::server_common::fromEvent<keto::proto::CheckForAccount>(
            keto::server_common::processEvent(keto::server_common::toEvent<keto::proto::CheckForAccount>(
            keto::server_common::Events::CHECK_ACCOUNT_MESSAGE,checkForAccount)));
    if (checkForAccount.found()) {
        // route
        keto::proto::MessageWrapperResponse response;
        response.set_success(true);
        response.set_result("found");
        return keto::server_common::toEvent<keto::proto::MessageWrapperResponse>(response);
    }
    
    std::cout << "Process the message : " << messageWrapper.messagetype() << std::endl;
    
    keto::proto::MessageWrapperResponse response;
    response.set_success(true);
    response.set_result("to peer");
    return keto::server_common::toEvent<keto::proto::MessageWrapperResponse>(response);
}

}
}