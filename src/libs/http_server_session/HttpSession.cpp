/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HttpSession.cpp
 * Author: ubuntu
 * 
 * Created on February 19, 2018, 11:07 AM
 */

#include <iostream>

#include "KeyStore.pb.h"

#include "keto/server_common/EventUtils.hpp"
#include "keto/server_common/Events.hpp"
#include "keto/server_common/EventServiceHelpers.hpp"

#include "keto/server_session/HttpSession.hpp"
#include "keto/server_common/ServerInfo.hpp"
#include "keto/crypto/SessionHashGenerator.hpp"
#include "keto/crypto/SecureVectorUtils.hpp"



namespace keto {
namespace server_session {


HttpSession::HttpSession(const std::vector<uint8_t>& clientHash) :
    clientHash(clientHash) {
    keto::crypto::SessionHashGenerator hashGenerator(
            clientHash,
            keto::server_common::ServerInfo::getInstance()->getAccountHash());
    this->sessionHash = hashGenerator.getHash();
    
    // create a session key
    keto::proto::SessionKeyRequest sessionKeyRequest;
    sessionKeyRequest.set_session_hash(
        keto::server_common::VectorUtils().copyVectorToString(this->sessionHash));
    
    keto::proto::SessionKeyResponse sessionKeyResponse = 
            keto::server_common::fromEvent<keto::proto::SessionKeyResponse>(keto::server_common::processEvent(keto::server_common::toEvent<keto::proto::SessionKeyRequest>(
            keto::server_common::Events::REQUEST_SESSION_KEY,sessionKeyRequest)));
    
    this->sessionKey = keto::crypto::SecureVectorUtils().copyToSecure(
            keto::server_common::VectorUtils().copyStringToVector(
            sessionKeyResponse.session_key()));
    
    
    this->createTime = std::chrono::system_clock::now();
    
}

HttpSession::~HttpSession() {
    keto::proto::SessionKeyExpireRequest sessionKeyExpireRequest;
    sessionKeyExpireRequest.set_session_hash(
            keto::server_common::VectorUtils().copyVectorToString(this->sessionHash));
    keto::server_common::triggerEvent(keto::server_common::toEvent<keto::proto::SessionKeyExpireRequest>(
            keto::server_common::Events::REMOVE_SESSION_KEY,sessionKeyExpireRequest));
}

std::vector<uint8_t> HttpSession::getClientHash() {
    this->touch();
    return this->clientHash;
}


std::vector<uint8_t> HttpSession::getSessionHash() {
    this->touch();
    return this->sessionHash;
}

keto::crypto::SecureVector HttpSession::getSessionKey() {
    this->touch();
    return this->sessionKey;
}

std::chrono::system_clock::time_point HttpSession::getCreateTime() {
    return this->createTime;
}


std::chrono::system_clock::time_point HttpSession::getTouchTime() {
    return this->touchTime;
}

void HttpSession::touch() {
    this->touchTime = std::chrono::system_clock::now();
}

}
}