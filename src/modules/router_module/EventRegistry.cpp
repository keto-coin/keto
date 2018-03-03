/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EventRegistry.cpp
 * Author: ubuntu
 * 
 * Created on March 3, 2018, 10:25 AM
 */

#include "keto/router/EventRegistry.hpp"
#include "keto/router/RouterService.hpp"

#include "keto/server_common/Events.hpp"
#include "keto/server_common/EventServiceHelpers.hpp"
#include "include/keto/router/RouterService.hpp"


namespace keto {
namespace router {


EventRegistry::EventRegistry() {
}

EventRegistry::~EventRegistry() {
}

keto::event::Event EventRegistry::routeMessage(const keto::event::Event& event) {
    return RouterService::getInstance()->routeMessage(event);
}

void EventRegistry::registerEventHandlers() {
    keto::server_common::registerEventHandler (
            keto::server_common::Events::ROUTE_MESSAGE,
            &keto::router::EventRegistry::routeMessage);

}

void EventRegistry::deregisterEventHandlers() {
    keto::server_common::deregisterEventHandler(keto::server_common::Events::ROUTE_MESSAGE);
}


}
}