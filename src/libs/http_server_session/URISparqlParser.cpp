/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   URISparqlParser.cpp
 * Author: ubuntu
 * 
 * Created on March 29, 2018, 6:19 AM
 */

#include "keto/server_session/URISparqlParser.hpp"
#include "keto/server_common/URLUtils.hpp"
#include "keto/server_session/Exception.hpp"
#include "keto/common/HttpEndPoints.hpp"

namespace keto {
namespace server_session {


URISparqlParser::URISparqlParser(const std::string& uri,const std::string& body) {
    // remove data segment from path
    std::string subUri = uri.substr(strlen(keto::common::HttpEndPoints::DATA_QUERY));
    int nextSlash = subUri.find("/");
    this->accountHash = subUri.substr(0,nextSlash);
    subUri = subUri.substr(nextSlash+1);
    int queryBegin = subUri.find(QUERY_PARAM);
    if (queryBegin != std::string::npos) {
        int queryEnd = subUri.find("&",queryBegin);
        this->query = keto::server_common::URLUtils::unescape(
                subUri.substr(queryBegin + strlen(QUERY_PARAM),queryEnd));
    } else if ((queryBegin = body.find(QUERY_PARAM)) != std::string::npos) {
        int queryEnd = subUri.find("&",queryBegin);
        this->query = keto::server_common::URLUtils::unescape(
                subUri.substr(queryBegin + strlen(QUERY_PARAM),queryEnd));
    } else {
        BOOST_THROW_EXCEPTION(keto::server_session::InvalidSparqlRequestException());
    }
}

URISparqlParser::~URISparqlParser() {
}

std::string URISparqlParser::getAccountHash() {
    return this->accountHash;
}

std::string URISparqlParser::getQuery() {
    return this->query;
}




}
}