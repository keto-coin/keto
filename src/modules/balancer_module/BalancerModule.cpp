/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BalancerModule.cpp
 * Author: ubuntu
 * 
 * Created on February 10, 2018, 1:36 PM
 */

#include "keto/balancer/BalancerModule.hpp"

namespace keto {
namespace balancer {


BalancerModule::BalancerModule() {
}

BalancerModule::~BalancerModule() {
}

// meta methods
const std::string BalancerModule::getName() const {
    return "BalancerModule";
}


const std::string BalancerModule::getDescription() const{
    return "The Balancer Module responsible for managing the balancing and filtering of transactions.";
}


const std::string BalancerModule::getVersion() const{
    return keto::common::MetaInfo::VERSION;
}


}
}