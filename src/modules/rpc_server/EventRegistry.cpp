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

#include "keto/rpc_server/EventRegistry.hpp"
#include "keto/rpc_server/RpcServerService.hpp"
#include "include/keto/rpc_server/RpcServerService.hpp"

#include "keto/server_common/Events.hpp"
#include "keto/server_common/EventServiceHelpers.hpp"


namespace keto {
namespace rpc_server {


EventRegistry::EventRegistry() {
}

EventRegistry::~EventRegistry() {
}


void EventRegistry::registerEventHandlers() {
    keto::server_common::registerEventHandler (
            keto::server_common::Events::RPC_SEND_MESSAGE,
            &keto::rpc_server::EventRegistry::sendMessage);
}

void EventRegistry::deregisterEventHandlers() {
    keto::server_common::deregisterEventHandler (
            keto::server_common::Events::RPC_SEND_MESSAGE);
}

keto::event::Event EventRegistry::sendMessage(const keto::event::Event& event) {
    return RpcServerService::getInstance()->sendMessage(event);
}

}
}