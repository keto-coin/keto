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


namespace keto {
namespace server_session {


HttpSessionManager::HttpSessionManager() {
}


HttpSessionManager::~HttpSessionManager() {
}

std::string HttpSessionManager::processHello(const std::string& hello) {
    keto::proto::ClientHello clientHello;\
    std::cout << "String to parse : " << hello << std::endl;
    if (clientHello.ParseFromString(hello)) {
        std::cout << "Process the hello " << clientHello.version() << std::endl;
    } else {
        std::cout << "Failed to deserialize " << std::endl;
    }
    
    std::string result;
    keto::proto::ClientResponse response;
    response.set_response(keto::proto::HelloResponse::WELCOME);
    response.SerializeToString(&result);
    return result;
}
    

}
}