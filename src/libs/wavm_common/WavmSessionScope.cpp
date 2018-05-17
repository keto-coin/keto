/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   WavmSessionScope.cpp
 * Author: ubuntu
 * 
 * Created on May 10, 2018, 4:44 PM
 */

#include "keto/wavm_common/WavmSessionScope.hpp"
#include "keto/wavm_common/WavmSessionManager.hpp"

namespace keto {
namespace wavm_common {

WavmSessionScope::WavmSessionScope(keto::proto::SandboxCommandMessage& sandboxCommandMessage) {
    keto::wavm_common::WavmSessionManager::getInstance()->initWavmSession(sandboxCommandMessage);
}

WavmSessionScope::~WavmSessionScope() {
    keto::wavm_common::WavmSessionManager::getInstance()->finWavmSession();
}

WavmSessionPtr WavmSessionScope::getSession() {
    return keto::wavm_common::WavmSessionManager::getInstance()->getWavmSession();
}

}
}