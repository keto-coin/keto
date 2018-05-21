/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RDFURLUtils.cpp
 * Author: ubuntu
 * 
 * Created on May 15, 2018, 10:58 AM
 */

#include "keto/wavm_common/RDFURLUtils.hpp"

#include <iostream>
#include <string>
#include <sstream>

namespace keto {
namespace wavm_common {


RDFURLUtils::RDFURLUtils(const std::string& url) {
    int pos = url.find("#");
    this->modelBaseUrl = url.substr(0,pos);
    this->modelName = url.substr(pos+1);
}

RDFURLUtils::~RDFURLUtils() {
}

std::string RDFURLUtils::getModelName() {
    return this->modelName;
}

std::string RDFURLUtils::getModelBaseUrl() {
    return this->modelBaseUrl;
}

std::string RDFURLUtils::buildSubjectUrl(const std::string& id) {
    std::stringstream ss;
    ss << this->modelBaseUrl << "#" << this->modelName << "/" << id;
    return ss.str();
}

std::string RDFURLUtils::buildPredicateUrl(const std::string& predicate) {
    std::stringstream ss;
    ss << this->modelBaseUrl << "#" << predicate;
    return ss.str();
}

}
}