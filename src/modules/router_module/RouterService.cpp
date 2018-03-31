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
#include <vector>

#include "BlockChain.pb.h"

#include "keto/router/RouterService.hpp"
#include "keto/server_common/Events.hpp"
#include "keto/server_common/EventServiceHelpers.hpp"
#include "keto/router_db/RouterStore.hpp"
#include "keto/server_common/ServerInfo.hpp"
#include "keto/server_common/Constants.hpp"
#include "keto/crypto/SecureVectorUtils.hpp"
#include "keto/router/RouterService.hpp"


#include "Protocol.pb.h"
#include "Account.pb.h"
#include "Route.pb.h"
#include "include/keto/router/RouterRegistry.hpp"

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
    std::cout << "The account hash : " << accountHash.getHash(keto::common::HEX) << std::endl;
    
    // look to see if the message account is for this server
    if (keto::crypto::SecureVectorUtils().copyFromSecure(
            accountHash.operator keto::crypto::SecureVector()) == keto::server_common::ServerInfo::getInstance()->getAccountHash()) {
        
        routeLocal(messageWrapper);
        // the result of the local routing 
        keto::proto::MessageWrapperResponse response;
        response.set_success(true);
        response.set_result("local");
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
        routeToAccount(messageWrapper);
        // route
        keto::proto::MessageWrapperResponse response;
        response.set_success(true);
        response.set_result("found");
        return keto::server_common::toEvent<keto::proto::MessageWrapperResponse>(response);
    }
    
    
    
    keto::proto::AccountRoutingStore accountRouting;
    if (keto::router_db::RouterStore::getInstance()->getAccountRouting(
            accountHash,accountRouting)) {
        
        // route
        keto::proto::MessageWrapperResponse response;
        response.set_success(true);
        response.set_result("routed");
        return keto::server_common::toEvent<keto::proto::MessageWrapperResponse>(response);
    }
    
    
    std::cout << "Process the message : " << messageWrapper.message_type() << std::endl;
    
    keto::proto::MessageWrapperResponse response;
    response.set_success(true);
    response.set_result("to peer");
    return keto::server_common::toEvent<keto::proto::MessageWrapperResponse>(response);
}

keto::event::Event RouterService::registerService(const keto::event::Event& event) {
    keto::proto::PushService  pushService = 
            keto::server_common::fromEvent<keto::proto::PushService>(event);
    
    RouterRegistry::getInstance()->registerService(
            keto::server_common::VectorUtils().copyStringToVector(pushService.account()),
            pushService.service_name());
    
    return keto::server_common::toEvent<keto::proto::PushService>(pushService);
}


void RouterService::routeLocal(keto::proto::MessageWrapper&  messageWrapper) {
    keto::proto::Transaction transaction;
    messageWrapper.msg().UnpackTo(&transaction);
    if (transaction.status() == keto::proto::TransactionStatus::DEBIT || 
            transaction.status() == keto::proto::TransactionStatus::INIT) {
        if (messageWrapper.message_operation() == keto::proto::MessageOperation::MESSAGE_INIT ||
                messageWrapper.message_operation() == keto::proto::MessageOperation::MESSAGE_ROUTE) {
            messageWrapper.set_message_operation(keto::proto::MessageOperation::MESSAGE_BALANCE);
            
        } else if (messageWrapper.message_operation() == 
                keto::proto::MessageOperation::MESSAGE_BALANCE) {
            
        } else if (messageWrapper.message_operation() == 
                keto::proto::MessageOperation::MESSAGE_BLOCK) {
            
        } else if (messageWrapper.message_operation() == 
                keto::proto::MessageOperation::MESSAGE_PROCESS) {
            
        }
        
    } else if (transaction.status() == keto::proto::TransactionStatus::CREDIT) {
        
        
    }
}

void RouterService::routeToAccount(keto::proto::MessageWrapper&  messageWrapper) {
    keto::proto::Transaction transaction;
    messageWrapper.msg().UnpackTo(&transaction);
    if (transaction.status() == keto::proto::TransactionStatus::DEBIT || 
            transaction.status() == keto::proto::TransactionStatus::INIT) {
        if (messageWrapper.message_operation() == keto::proto::MessageOperation::MESSAGE_INIT ||
                messageWrapper.message_operation() == keto::proto::MessageOperation::MESSAGE_ROUTE) {
            messageWrapper.set_message_operation(keto::proto::MessageOperation::MESSAGE_BALANCE);
            AccountHashVector accountHashVector = 
                    RouterRegistry::getInstance()->getAccount(
                    keto::server_common::Constants::SERVICE::BALANCE);
            messageWrapper.set_account_hash(keto::server_common::VectorUtils().copyVectorToString(accountHashVector));
            if (RouterRegistry::getInstance()->isAccountLocal(accountHashVector)) {
                keto::server_common::triggerEvent(keto::server_common::toEvent<keto::proto::MessageWrapper>(
                        keto::server_common::Events::BALANCER_MESSAGE,messageWrapper));
            } else {
                keto::server_common::triggerEvent(keto::server_common::toEvent<keto::proto::MessageWrapper>(
                        keto::server_common::Events::RPC_SEND_MESSAGE,messageWrapper));
            }
        }
        
    } else if (transaction.status() == keto::proto::TransactionStatus::CREDIT) {
        if (messageWrapper.message_operation() == keto::proto::MessageOperation::MESSAGE_ROUTE) {
            messageWrapper.set_message_operation(keto::proto::MessageOperation::MESSAGE_BALANCE);
            AccountHashVector accountHashVector = 
                    RouterRegistry::getInstance()->getAccount(
                    keto::server_common::Constants::SERVICE::BALANCE);
            messageWrapper.set_account_hash(keto::server_common::VectorUtils().copyVectorToString(accountHashVector));
            if (RouterRegistry::getInstance()->isAccountLocal(accountHashVector)) {
                keto::server_common::triggerEvent(keto::server_common::toEvent<keto::proto::MessageWrapper>(
                        keto::server_common::Events::BALANCER_MESSAGE,messageWrapper));
            } else {
                keto::server_common::triggerEvent(keto::server_common::toEvent<keto::proto::MessageWrapper>(
                        keto::server_common::Events::RPC_SEND_MESSAGE,messageWrapper));
            }
        }
    }
}

}
}