/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EnvironmentManager.cpp
 * Author: Brett Chaldecott
 * 
 * Created on January 10, 2018, 12:15 PM
 */


#include "keto/environment/EnvironmentManager.hpp"

namespace keto {
namespace environment {   


static std::shared_ptr<EnvironmentManager> singleton;


EnvironmentManager::EnvironmentManager(const std::string& config,
        const po::options_description& optionDescription,
        int argc, char** argv) {
    envPtr = std::make_shared<Env>();
    configPtr = std::make_shared<Config>(envPtr->getInstallDir(),config,optionDescription,argc,
            argv);
    logManagerPtr = std::make_shared<LogManager>(envPtr,configPtr);
    
}

EnvironmentManager::~EnvironmentManager() {
}

std::shared_ptr<EnvironmentManager> EnvironmentManager::init(const std::string& config,
        const po::options_description& optionDescription,
        int argc, char** argv) {
    if (singleton) {
        return singleton;
    }
    return singleton = std::make_shared<EnvironmentManager>(config,optionDescription,argc,argv);
}


std::shared_ptr<EnvironmentManager> EnvironmentManager::getInstance() {
    return singleton;
}


std::shared_ptr<Env> EnvironmentManager::getEnv() {
    return envPtr;
}

std::shared_ptr<Config> EnvironmentManager::getConfig() {
    return configPtr;
}

std::shared_ptr<LogManager> EnvironmentManager::getLogManager() {
    return logManagerPtr;
}
    

}
}