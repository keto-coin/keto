/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HttpTransactionManager.cpp
 * Author: ubuntu
 * 
 * Created on March 2, 2018, 7:11 AM
 */

#include <boost/beast/http/message.hpp>

#include "BlockChain.pb.h"
#include "Protocol.pb.h"
#include "google/protobuf/any.h"

#include "keto/common/HttpEndPoints.hpp"
#include "keto/common/StringCodec.hpp"
#include "keto/asn1/HashHelper.hpp"

#include "keto/server_common/EventUtils.hpp"
#include "keto/server_common/Events.hpp"
#include "keto/server_common/EventServiceHelpers.hpp"

#include "keto/server_session/HttpTransactionManager.hpp"
#include "keto/server_session/HttpSessionManager.hpp"
#include "keto/server_session/HttpSession.hpp"
#include "keto/server_session/Exception.hpp"
#include "keto/crypto/SecureVectorUtils.hpp"


namespace keto {
namespace server_session {


HttpTransactionManager::HttpTransactionManager(
    std::shared_ptr<HttpSessionManager>& httpSessionManagerPtr) : 
    httpSessionManagerPtr(httpSessionManagerPtr) {
    
}

HttpTransactionManager::~HttpTransactionManager() {
}

std::string HttpTransactionManager::processTransaction(
        boost::beast::http::request<boost::beast::http::string_body>& req,
        const std::string& transactionMsg) {
    std::string sessionHash = (const std::string&)req.base().at(keto::common::HttpEndPoints::HEADER_SESSION_HASH);
    keto::asn1::HashHelper hashHelper(
            sessionHash,keto::common::HEX);
    std::vector<uint8_t> vectorHash = keto::crypto::SecureVectorUtils().copyFromSecure(hashHelper);
    if (!httpSessionManagerPtr->isValid(vectorHash)) {
        BOOST_THROW_EXCEPTION(keto::server_session::InvalidSessionException());
    }
    std::shared_ptr<HttpSession> httpSession = 
            httpSessionManagerPtr->getSession(vectorHash);
    
    keto::proto::Transaction transaction;
    
    if (!transaction.ParseFromString(transactionMsg)) {
        BOOST_THROW_EXCEPTION(keto::server_session::MessageDeserializationException(
                "Failed to deserialized the transaction message."));
    }
    
    keto::proto::MessageWrapper wrapper;
    wrapper.set_version(1);
    wrapper.set_session_hash(vectorHash.data(),vectorHash.size());
    wrapper.set_account_hash(transaction.activeaccount());
    wrapper.set_message_type(keto::proto::MessageType::MESSAGE_TYPE_TRANSACTION);
    wrapper.set_message_operation(keto::proto::MessageOperation::MESSAGE_INIT);
    google::protobuf::Any* any = new google::protobuf::Any();
    any->PackFrom(transaction);
    wrapper.set_allocated_msg(any);
    
    keto::proto::MessageWrapperResponse  messageWrapperResponse = 
            keto::server_common::fromEvent<keto::proto::MessageWrapperResponse>(
            keto::server_common::processEvent(keto::server_common::toEvent<keto::proto::MessageWrapper>(
            keto::server_common::Events::ROUTE_MESSAGE,wrapper)));
    
    return messageWrapperResponse.result();
}
    
}
}