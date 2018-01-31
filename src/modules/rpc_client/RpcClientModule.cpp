/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RpcClientModule.cpp
 * Author: ubuntu
 * 
 * Created on January 20, 2018, 1:45 PM
 */

#include "keto/rpc_client/RpcClientModule.hpp"
#include "keto/common/MetaInfo.hpp"

namespace keto {
namespace rpc_client {

RpcClientModule::RpcClientModule() {
}

RpcClientModule::~RpcClientModule() {
}

// meta methods
const std::string RpcClientModule::getName() const {
    return "RpcClientModule";
}

const std::string RpcClientModule::getDescription() const {
    return "The rpc client responsible for all RPC out going calls";
}

const std::string RpcClientModule::getVersion() const {
    return keto::common::MetaInfo::VERSION;
}


}
}
