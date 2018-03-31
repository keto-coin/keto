/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RpcServerService.cpp
 * Author: ubuntu
 * 
 * Created on March 31, 2018, 10:08 AM
 */

#include <memory>
#include <iostream>

#include "Protocol.pb.h"

#include "keto/server_common/Events.hpp"
#include "keto/server_common/EventServiceHelpers.hpp"

#include "keto/rpc_server/RpcServerService.hpp"

namespace keto {
namespace rpc_server {

static RpcServerServicePtr singleton;
    
RpcServerService::RpcServerService() {
}

RpcServerService::~RpcServerService() {
}

RpcServerServicePtr RpcServerService::init() {
    return singleton = std::make_shared<RpcServerService>();
}

void RpcServerService::fin() {
    singleton.reset();
}

RpcServerServicePtr RpcServerService::getInstance() {
    return singleton;
}

keto::event::Event RpcServerService::sendMessage(const keto::event::Event& event) {
    keto::proto::MessageWrapper  messageWrapper = 
            keto::server_common::fromEvent<keto::proto::MessageWrapper>(event);
    
    std::cout << "The rpc says hi" << std::endl;
    
    keto::proto::MessageWrapperResponse response;
    response.set_success(true);
    response.set_result("out_bound");
    return keto::server_common::toEvent<keto::proto::MessageWrapperResponse>(response);
}

}
}