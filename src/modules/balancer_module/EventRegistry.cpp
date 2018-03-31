/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EventRegistry.cpp
 * Author: ubuntu
 * 
 * Created on March 8, 2018, 3:15 AM
 */

#include "keto/balancer/EventRegistry.hpp"
#include "keto/balancer/BalancerService.hpp"

#include "keto/server_common/Events.hpp"
#include "keto/server_common/EventServiceHelpers.hpp"


namespace keto {
namespace balancer {


EventRegistry::EventRegistry() {
}

EventRegistry::~EventRegistry() {
}


void EventRegistry::registerEventHandlers() {
    keto::server_common::registerEventHandler (
            keto::server_common::Events::BALANCER_MESSAGE,
            &keto::balancer::EventRegistry::balanceMessage);
}

void EventRegistry::deregisterEventHandlers() {
    keto::server_common::deregisterEventHandler (
            keto::server_common::Events::BALANCER_MESSAGE);
}

keto::event::Event EventRegistry::balanceMessage(const keto::event::Event& event) {
    return BalancerService::getInstance()->balanceMessage(event);
}

}
}