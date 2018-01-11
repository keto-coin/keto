/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EnvironmentManager.cpp
 * Author: ubuntu
 * 
 * Created on January 10, 2018, 12:15 PM
 */


#include "keto/environment/EnvironmentManager.hpp"

namespace keto {
namespace environment {   


static std::shared_ptr<EnvironmentManager> singleton = 0;


EnvironmentManager::EnvironmentManager() {
    envSharedPtr = std::make_shared<Env>();
    
}


EnvironmentManager::~EnvironmentManager() {
}

std::shared_ptr<EnvironmentManager> EnvironmentManager::init() {
    if (singleton) {
        return singleton;
    }
    return singleton = std::make_shared<EnvironmentManager>();
}

std::shared_ptr<EnvironmentManager> EnvironmentManager::getInstance() {
    if (!singleton) {
        singleton = std::make_shared<EnvironmentManager>();
    }
    return singleton;
}


std::shared_ptr<Env> EnvironmentManager::getEnv() {
    return envSharedPtr;
}

}
}