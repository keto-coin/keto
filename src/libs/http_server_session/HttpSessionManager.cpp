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
#include <memory>

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <condition_variable>

#include <botan/hex.h>
#include "KeyStore.pb.h"

#include "keto/server_common/VectorUtils.hpp"
#include "keto/server_session/HttpSessionManager.hpp"

#include "keto/server_common/EventUtils.hpp"
#include "keto/server_common/Events.hpp"
#include "keto/server_common/EventServiceHelpers.hpp"
#include "keto/server_session/Exception.hpp"
#include "keto/server_common/ServerInfo.hpp"
#include "keto/crypto/KeyLoader.hpp"
#include "keto/crypto/SignatureVerification.hpp"
#include "keto/crypto/SecureVectorUtils.hpp"
#include "keto/crypto/SessionHashGenerator.hpp"
#include "keto/crypto/HashGenerator.hpp"
#include "keto/event/EventServiceInterface.hpp"

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
    
    // this method is called to validate the client
    std::shared_ptr<Botan::Public_Key> publicKey = this->validateRemoteHash(clientHello);
    if (!publicKey) {
        std::string result;
        keto::proto::ClientResponse response;
        response.set_response(keto::proto::HelloResponse::GO_AWAY);
        response.SerializeToString(&result);
        return result;
    }
    
    
    keto::crypto::SessionHashGenerator hashGenerator(
            keto::server_common::VectorUtils().copyStringToVector(
            clientHello.client_hash()),
            keto::server_common::ServerInfo::getInstance()->getAccountHash());
    
    // create a session key
    SessionKeyRequest sessionKeyRequest;
    sessionKeyRequest.set_session_hash(keto::server_common::VectorUtils().copyVectorToString(
        hashGenerator.getHash()));
    
    //keto::event::Event processEvent = keto::server_common::toEvent<SessionKeyRequest>(
    //        keto::server_common::Events::REQUEST_SESSION_KEY,sessionKeyRequest);
    
    keto::event::Event resultEvent = keto::server_common::processEvent(keto::server_common::toEvent<SessionKeyRequest>(
            keto::server_common::Events::REQUEST_SESSION_KEY,sessionKeyRequest));
    //keto::event::Event resultEvent = std::dynamic_pointer_cast<keto::event::EventServiceInterface>(keto::module::ModuleManager::getInstance()->getModule(keto::event::EventServiceInterface::KETO_EVENT_SERVICE_MODULE))->processEvent(event);
    
    //SessionKeyResponse sessionKeyResponse = 
    //        keto::server_common::fromEvent<SessionKeyResponse>(
    //        resultEvent);
    
    std::string result;
    keto::proto::ClientResponse response;
    response.set_response(keto::proto::HelloResponse::WELCOME);
    response.set_session_hash(sessionKeyRequest.session_hash());
    //response.set_session_key(sessionKeyResponse.session_key());
    response.SerializeToString(&result);
    return result;
}



std::shared_ptr<Botan::Public_Key> HttpSessionManager::validateRemoteHash(
    keto::proto::ClientHello& clientHello) {
    
    // retrieve a list of all the public keys
    boost::filesystem::path publicKeyPath =
            keto::server_common::ServerInfo::getInstance()->getPublicKeyPath();
    std::vector<boost::filesystem::path> files;                                // so we can sort them later
    std::copy(boost::filesystem::directory_iterator(publicKeyPath), 
            boost::filesystem::directory_iterator(), std::back_inserter(files));
    
    std::vector<uint8_t> clientHash = keto::server_common::VectorUtils().copyStringToVector(clientHello.client_hash());
    std::vector<uint8_t> signature = keto::server_common::VectorUtils().copyStringToVector(clientHello.signature());
    
    for (std::vector<boost::filesystem::path>::const_iterator it(files.begin()), 
            it_end(files.end()); it != it_end; ++it) {
        keto::crypto::KeyLoader loader(*it);
        std::shared_ptr<Botan::Public_Key> publicKey = loader.getPublicKey();
        
        std::vector<uint8_t> publicKeyHashVector = keto::crypto::SecureVectorUtils().copyFromSecure(keto::crypto::HashGenerator().generateHash(
            Botan::X509::BER_encode(*publicKey)));
        
        if (publicKeyHashVector == clientHash) {
            if (keto::crypto::SignatureVerification(publicKey,publicKeyHashVector).check(signature)) {
                return publicKey;
            } else {
                break;
            }
        }
    }
    return std::shared_ptr<Botan::Public_Key>();
}

}
}