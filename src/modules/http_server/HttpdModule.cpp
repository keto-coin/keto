/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HttpdModule.cpp
 * Author: ubuntu
 * 
 * Created on January 20, 2018, 12:44 PM
 */

#include "keto/http/HttpdModule.hpp"
#include "keto/common/MetaInfo.hpp"


namespace keto {
namespace http {

HttpdModule::HttpdModule() {
}


HttpdModule::~HttpdModule() {
}

// meta methods
const std::string HttpdModule::getName() const {
    return "HttpdModule";
}

const std::string HttpdModule::getDescription() const {
    return "The implementation of the httpd module";
}

const std::string HttpdModule::getVersion() const {
    return keto::common::MetaInfo::VERSION;
}


}
}