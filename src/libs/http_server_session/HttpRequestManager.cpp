/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HttpRequestManager.cpp
 * Author: ubuntu
 * 
 * Created on February 15, 2018, 10:05 AM
 */

#include <iostream>
#include <memory>
#include "keto/server_session/HttpRequestManager.hpp"

namespace keto {
namespace server_session {

static std::shared_ptr<HttpRequestManager> singleton;


HttpRequestManager::HttpRequestManager() {
    httpSessionManagerPtr = std::make_shared<HttpSessionManager>();
}

HttpRequestManager::~HttpRequestManager() {
}

bool
HttpRequestManager::checkRequest(boost::beast::http::request<boost::beast::http::string_body>& req) {
    boost::beast::string_view path = req.target();
    
    if (path.empty()) {
        return false;
    }
    std::string target = path.to_string();
    if (0 == target.compare(keto::common::HttpEndPoints::HAND_SHAKE)) {
        return true;
    }
    return false;
}

boost::beast::http::response<boost::beast::http::string_body>
HttpRequestManager::handle_request(
        boost::beast::http::request<boost::beast::http::string_body>& req) {
    boost::beast::string_view path = req.target();
    std::string target = path.to_string();
    std::string result;
    if (0 == target.compare(keto::common::HttpEndPoints::HAND_SHAKE)) {
        result = this->httpSessionManagerPtr->processHello(req.body());
    }
    boost::beast::http::response<boost::beast::http::string_body> response;
    response.set(boost::beast::http::field::server, BOOST_BEAST_VERSION_STRING);
    response.set(boost::beast::http::field::content_type, "text/html");
    response.keep_alive(req.keep_alive());
    response.body() = result;
    response.content_length(result.size());
    
    return response;
}

std::shared_ptr<HttpRequestManager> HttpRequestManager::init() {
    if (!singleton) {
        singleton = std::shared_ptr<HttpRequestManager>(
                new HttpRequestManager());
    }
    return singleton;
}


std::shared_ptr<HttpRequestManager> HttpRequestManager::getInstance() {
    return singleton;
}



}
}

