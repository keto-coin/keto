/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SandboxService.cpp
 * Author: ubuntu
 * 
 * Created on April 10, 2018, 8:33 AM
 */

#include <boost/filesystem/path.hpp>
#include <iostream>
#include <sstream>

#include <condition_variable>

#include "keto/sandbox/SandboxService.hpp"
#include "keto/wavm_common/WavmEngineManager.hpp"
#include "keto/environment/EnvironmentManager.hpp"
#include "include/keto/sandbox/SandboxService.hpp"


namespace keto {
namespace sandbox {

static SandboxServicePtr singleton;

SandboxService::SandboxService() {
    boost::filesystem::path helloFile =  
            keto::environment::EnvironmentManager::getInstance()->getEnv()->getInstallDir() / 
            "config/helloworld.wast";
    std::ifstream ifs(helloFile.string());
    char buffer[1024];
    char character;
    std::stringstream ss;
    while (ifs.get(character)) {
        ss << character;
    }
    this->code = ss.str();
}

SandboxService::~SandboxService() {
}


SandboxServicePtr SandboxService::init() {
    return singleton = std::make_shared<SandboxService>();
}

void SandboxService::fin() {
    singleton.reset();
}

SandboxServicePtr SandboxService::getInstance() {
    return singleton;
}

keto::event::Event SandboxService::executeActionMessage(const keto::event::Event& event) {
    
    keto::wavm_common::WavmEngineManager::getInstance()->getEngine(code)->execute();
    
    return event;
}

}
}