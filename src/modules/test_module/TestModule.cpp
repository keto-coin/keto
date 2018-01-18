/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestModule.cpp
 * Author: ubuntu
 * 
 * Created on January 18, 2018, 10:28 AM
 */

#include "keto/common/Log.hpp"
#include "keto/test/TestModule.hpp"

namespace keto {
namespace test {
        

TestModule::TestModule() {
    KETO_LOG_INFO << "The test module has been started";
}

TestModule::~TestModule() {
    KETO_LOG_INFO << "The test module has closed";
}


const std::string TestModule::getName() const {
    return "TestModule";
}

const std::string TestModule::getDescription() const {
    return "The example test module";
}

const std::string TestModule::getVersion() const {
    return "0.0.1";
}

}
}