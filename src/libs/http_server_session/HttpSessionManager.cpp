/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HttpSessionManager.cpp
 * Author: ubuntu
 * 
 * Created on February 15, 2018, 9:39 AM
 */

#include <iostream>

#include "keto/server_session/HttpSessionManager.hpp"

#include "HandShake.pb.h"

#include "keto/server_session/Exception.hpp"

namespace keto {
namespace server_session {


HttpSessionManager::HttpSessionManager() {
}


HttpSessionManager::~HttpSessionManager() {
}

std::string HttpSessionManager::processHello(const std::string& hello) {
    keto::proto::ClientHello clientHello;
    if (!clientHello.ParseFromString(hello)) {
        BOOST_THROW_EXCEPTION(keto::server_session::MessageDeserializationException(
                "Failed to deserialized the Client Hello message."));
    }
    
    std::string result;
    keto::proto::ClientResponse response;
    response.set_response(keto::proto::HelloResponse::GO_AWAY);
    response.SerializeToString(&result);
    return result;
}
    

}
}