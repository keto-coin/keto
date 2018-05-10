/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   WavmSessionManager.cpp
 * Author: ubuntu
 * 
 * Created on May 10, 2018, 11:01 AM
 */

#include <condition_variable>

#include "keto/wavm_common/WavmSessionManager.hpp"


namespace keto {
namespace wavm_common {

static WavmSessionManagerPtr singleton;
thread_local WavmSessionPtr WavmSessionManager::wavmSessionPtr;


WavmSessionManager::WavmSessionManager() {
}

WavmSessionManager::~WavmSessionManager() {
}

WavmSessionManagerPtr WavmSessionManager::init() {
    return singleton = std::shared_ptr<WavmSessionManager>();
}


void WavmSessionManager::fin() {
    singleton.reset();
}


WavmSessionManagerPtr WavmSessionManager::getInstance() {
    return singleton;
}


WavmSessionPtr WavmSessionManager::initWavmSession(
    const keto::proto::SandboxCommandMessage& sandboxCommandMessage) {
    return wavmSessionPtr = std::make_shared<WavmSession>(sandboxCommandMessage);
}


WavmSessionPtr WavmSessionManager::getWavmSession() {
    return wavmSessionPtr;
}

void WavmSessionManager::finWavmSession() {
    wavmSessionPtr.reset();
}


}
}