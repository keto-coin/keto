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

#include "keto/common/HttpEndPoints.hpp"
#include "keto/common/StringCodec.hpp"
#include "keto/asn1/HashHelper.hpp"
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
    keto::asn1::HashHelper hashHelper(
            (const std::string&)req.base().at(keto::common::HttpEndPoints::HEADER_SESSION_HASH),
            keto::common::HEX);
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
    
    
    return "ACCEPTED";
}
    
}
}