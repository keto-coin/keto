/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BlockModule.cpp
 * Author: ubuntu
 * 
 * Created on February 10, 2018, 3:21 PM
 */

#include "keto/block/BlockModule.hpp"

namespace keto {
namespace block {


BlockModule::BlockModule() {
}

BlockModule::~BlockModule() {
}


// meta methods
const std::string BlockModule::getName() const {
    return "BlockModule";
}


const std::string BlockModule::getDescription() const {
    return "The Block Module responsible for building blocks.";

}


const std::string BlockModule::getVersion() const {
    return keto::common::MetaInfo::VERSION;
}


}
}