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
    
    keto::proto::MessageWrapperResponse response;
    response.set_success(true);
    response.set_result("balanced");
    return keto::server_common::toEvent<keto::proto::MessageWrapperResponse>(response);
}

}
}