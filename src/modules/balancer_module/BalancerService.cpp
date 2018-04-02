/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BalancerService.cpp
 * Author: ubuntu
 * 
 * Created on March 31, 2018, 9:50 AM
 */

#include <condition_variable>
#include <iostream>

#include "Protocol.pb.h"

#include "keto/server_common/Events.hpp"
#include "keto/server_common/EventServiceHelpers.hpp"

#include "keto/balancer/BalancerService.hpp"
#include "keto/balancer/BlockRouting.hpp"
#include "include/keto/balancer/BlockRouting.hpp"

namespace keto {
namespace balancer {

static BalancerServicePtr singleton;
    
BalancerService::BalancerService() {
}

BalancerService::~BalancerService() {
}

BalancerServicePtr BalancerService::init() {
    return singleton = std::make_shared<BalancerService>();
}

void BalancerService::fin() {
    singleton.reset();
}

BalancerServicePtr BalancerService::getInstance() {
    return singleton;
}

keto::event::Event BalancerService::balanceMessage(const keto::event::Event& event) {
    keto::proto::MessageWrapper  messageWrapper = 
            keto::server_common::fromEvent<keto::proto::MessageWrapper>(event);
    std::cout << "The balancer says hi" << std::endl;
    messageWrapper.set_message_operation(keto::proto::MessageOperation::MESSAGE_BLOCK);
    AccountHashVector accountHashVector = BlockRouting::getInstance()->getBlockAccount(
            keto::server_common::VectorUtils().copyStringToVector(messageWrapper.account_hash()));
    messageWrapper.set_account_hash(keto::server_common::VectorUtils().copyVectorToString(accountHashVector));
    if (accountHashVector == keto::server_common::ServerInfo::getInstance()->getAccountHash()) {
        keto::server_common::triggerEvent(keto::server_common::toEvent<keto::proto::MessageWrapper>(
                    keto::server_common::Events::BLOCK_MESSAGE,messageWrapper));
    } else {
        keto::server_common::triggerEvent(keto::server_common::toEvent<keto::proto::MessageWrapper>(
                    keto::server_common::Events::RPC_SEND_MESSAGE,messageWrapper));
    }
    keto::proto::MessageWrapperResponse response;
    response.set_success(true);
    response.set_result("balanced");
    return keto::server_common::toEvent<keto::proto::MessageWrapperResponse>(response);
}

}
}