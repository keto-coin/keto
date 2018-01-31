/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RpcServerModule.cpp
 * Author: ubuntu
 * 
 * Created on January 20, 2018, 2:46 PM
 */

#include <boost/beast.hpp>
#include <boost/asio/strand.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/stream.hpp>

#include "keto/rpc_server/RpcServerModule.hpp"
#include "keto/common/MetaInfo.hpp"

namespace keto {
namespace rpc_server {


RpcServerModule::RpcServerModule() {
}

RpcServerModule::~RpcServerModule() {
}

// meta methods
const std::string RpcServerModule::getName() const {
    return "RpcServerModule";
}

const std::string RpcServerModule::getDescription() const {
    return "The RPC Server End point used by the RPC Client";
}

const std::string RpcServerModule::getVersion() const {
    return keto::common::MetaInfo::VERSION;
}


}
}