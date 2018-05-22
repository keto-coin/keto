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


namespace keto {
namespace router {


EventRegistry::EventRegistry() {
}

EventRegistry::~EventRegistry() {
}

keto::event::Event EventRegistry::routeMessage(const keto::event::Event& event) {
    return RouterService::getInstance()->routeMessage(event);
}


keto::event::Event EventRegistry::updateStateRouteMessage(const keto::event::Event& event) {
    return RouterService::getInstance()->updateStateRouteMessage(event);
}
    

keto::event::Event EventRegistry::registerService(const keto::event::Event& event) {
    return RouterService::getInstance()->registerService(event);
}



void EventRegistry::registerEventHandlers() {
    keto::server_common::registerEventHandler (
            keto::server_common::Events::ROUTE_MESSAGE,
            &keto::router::EventRegistry::routeMessage);
    keto::server_common::registerEventHandler (
            keto::server_common::Events::UPDATE_STATUS_ROUTE_MESSSAGE,
            &keto::router::EventRegistry::updateStateRouteMessage);
    keto::server_common::registerEventHandler (
            keto::server_common::Events::REGISTER_SERVICE_MESSAGE,
            &keto::router::EventRegistry::registerService);
}

void EventRegistry::deregisterEventHandlers() {
    keto::server_common::deregisterEventHandler(keto::server_common::Events::REGISTER_SERVICE_MESSAGE);
    keto::server_common::deregisterEventHandler(keto::server_common::Events::UPDATE_STATUS_ROUTE_MESSSAGE);
    keto::server_common::deregisterEventHandler(keto::server_common::Events::ROUTE_MESSAGE);
}


}
}