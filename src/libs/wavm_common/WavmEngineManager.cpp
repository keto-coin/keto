/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   WavmEngineManager.cpp
 * Author: ubuntu
 * 
 * Created on April 9, 2018, 9:12 AM
 */

#include <condition_variable>

#include "keto/wavm_common/WavmEngineManager.hpp"
#include "keto/wavm_common/WavmEngineWrapper.hpp"

namespace keto {
namespace wavm_common {
    
static WavmEngineManagerPtr singleton;
    
WavmEngineManager::WavmEngineManager() {
}

WavmEngineManager::~WavmEngineManager() {
    
}

WavmEngineManagerPtr WavmEngineManager::init() {
    return singleton = std::make_shared<WavmEngineManager>();
}


void WavmEngineManager::fin() {
    singleton.reset();
}

WavmEngineManagerPtr WavmEngineManager::getInstance() {
    return singleton;
}


WavmEngineWrapperPtr WavmEngineManager::getEngine(const std::string& wast) {
    return WavmEngineWrapperPtr(new WavmEngineWrapper(wast)); 
}


}
}
