/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RouterModule.cpp
 * Author: ubuntu
 * 
 * Created on February 9, 2018, 11:11 AM
 */

#include "keto/router/RouterModule.hpp"

namespace keto {
namespace router {


RouterModule::RouterModule() {
}

RouterModule::~RouterModule() {
}

// meta methods
const std::string RouterModule::getName() const {
    return "RouterModule";
}

const std::string RouterModule::getDescription() const {
    return "The Router Module responsible for managing the routing of messages.";
}

const std::string RouterModule::getVersion() const {
    return keto::common::MetaInfo::VERSION;
}


}
}