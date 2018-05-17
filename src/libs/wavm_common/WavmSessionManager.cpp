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

#include "keto/environment/EnvironmentManager.hpp"
#include "keto/environment/Config.hpp"

#include "keto/wavm_common/WavmSessionManager.hpp"
#include "keto/server_common/Constants.hpp"
#include "keto/wavm_common/Exception.hpp"


namespace keto {
namespace wavm_common {

static WavmSessionManagerPtr singleton;
thread_local WavmSessionPtr WavmSessionManager::wavmSessionPtr;


WavmSessionManager::WavmSessionManager() {
    std::cout << "From the wavm session" << std::endl;
    std::shared_ptr<keto::environment::Config> config = 
            keto::environment::EnvironmentManager::getInstance()->getConfig();
    if (!config->getVariablesMap().count(keto::server_common::Constants::PRIVATE_KEY)) {
        BOOST_THROW_EXCEPTION(keto::wavm_common::PrivateKeyNotFoundException());
    }
    std::string privateKeyPath = 
            config->getVariablesMap()[keto::server_common::Constants::PRIVATE_KEY].as<std::string>();
    if (!config->getVariablesMap().count(keto::server_common::Constants::PUBLIC_KEY)) {
        BOOST_THROW_EXCEPTION(keto::wavm_common::PublicKeyNotFoundException());
    }
    std::string publicKeyPath = 
            config->getVariablesMap()[keto::server_common::Constants::PUBLIC_KEY].as<std::string>();
    this->keyLoaderPtr = std::make_shared<keto::crypto::KeyLoader>(privateKeyPath,
            publicKeyPath);
}

WavmSessionManager::~WavmSessionManager() {
}

WavmSessionManagerPtr WavmSessionManager::init() {
    return singleton = std::make_shared<WavmSessionManager>();
}


void WavmSessionManager::fin() {
    singleton.reset();
}


WavmSessionManagerPtr WavmSessionManager::getInstance() {
    return singleton;
}


WavmSessionPtr WavmSessionManager::initWavmSession(
    const keto::proto::SandboxCommandMessage& sandboxCommandMessage) {
    return wavmSessionPtr = std::make_shared<WavmSession>(sandboxCommandMessage,
            this->keyLoaderPtr);
}


WavmSessionPtr WavmSessionManager::getWavmSession() {
    return wavmSessionPtr;
}

void WavmSessionManager::finWavmSession() {
    wavmSessionPtr.reset();
}


}
}