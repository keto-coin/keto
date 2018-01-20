/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   VersionManagerModule.cpp
 * Author: ubuntu
 * 
 * Created on January 20, 2018, 5:03 PM
 */

#include "keto/version_manager/VersionManagerModule.hpp"

namespace keto {
namespace version_manager {

VersionManagerModule::VersionManagerModule() {
}

VersionManagerModule::~VersionManagerModule() {
}


// meta methods
const std::string VersionManagerModule::getName() const {
    return "VersionManagerModule";
}

const std::string VersionManagerModule::getDescription() const {
    return "The Version Manager Module responsible for maintaining the version of keto running.";
}

const std::string VersionManagerModule::getVersion() const {
    return "0.1.0";
}

}
}
