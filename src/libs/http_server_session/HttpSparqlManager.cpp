/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HttpSparqlManager.cpp
 * Author: ubuntu
 * 
 * Created on March 28, 2018, 11:02 AM
 */

#include <string>
#include <iostream>


#include "keto/asn1/HashHelper.hpp"
#include "keto/common/HttpEndPoints.hpp"
#include "keto/crypto/SecureVectorUtils.hpp"
#include "keto/server_session/HttpSparqlManager.hpp"

namespace keto{
namespace server_session {

HttpSparqlManager::HttpSparqlManager(std::shared_ptr<HttpSessionManager>& httpSessionManagerPtr) : 
    httpSessionManagerPtr(httpSessionManagerPtr) {
    
}

HttpSparqlManager::~HttpSparqlManager() {
    
}

std::string HttpSparqlManager::processTransaction(
        boost::beast::http::request<boost::beast::http::string_body>& req,
        const std::string& transactionMsg) {
    std::string sessionHash = (const std::string&)req.base().at(keto::common::HttpEndPoints::HEADER_SESSION_HASH);
    keto::asn1::HashHelper hashHelper(
            sessionHash,keto::common::HEX);
    std::vector<uint8_t> vectorHash = keto::crypto::SecureVectorUtils().copyFromSecure(hashHelper);
    
    boost::beast::string_view path = req.target();
    std::cout << "The path for the request is : " << path << std::endl;
    std::string target = path.to_string();
    std::string accountHexHash = target.substr(0,strlen(keto::common::HttpEndPoints::DATA_QUERY));
    
    //req.base().
    return "";
}

}
}