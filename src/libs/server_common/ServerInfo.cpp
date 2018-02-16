/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ServerInfo.cpp
 * Author: ubuntu
 * 
 * Created on February 16, 2018, 8:31 AM
 */

#include <mutex>
#include <sstream>

#include <botan/hex.h>


#include "keto/server_common/ServerInfo.hpp"
#include "keto/server_common/Constants.hpp"

#include "keto/environment/EnvironmentManager.hpp"
#include "keto/environment/Config.hpp"
#include "include/keto/server_common/ServerInfo.hpp"
#include "include/keto/server_common/Exception.hpp"

namespace keto {
namespace server_common {

static std::mutex singletonMutex;
static std::shared_ptr<ServerInfo> singleton;

ServerInfo::ServerInfo() {
    
    // retrieve the configuration
    std::shared_ptr<keto::environment::Config> config = 
            keto::environment::EnvironmentManager::getInstance()->getConfig();
    
    // retrieve the host information from the configuration file
    if (!config->getVariablesMap().count(keto::server_common::Constants::PUBLIC_KEY_DIR)) {
        BOOST_THROW_EXCEPTION(keto::server_common::NoPublicKeyDirectoryConfiguredException());
    }
    std::string publicKeyPath = 
            config->getVariablesMap()[keto::server_common::Constants::PUBLIC_KEY_DIR].as<std::string>();
    this->publicKeyPath =  
            keto::environment::EnvironmentManager::getInstance()->getEnv()->getInstallDir() / publicKeyPath;
    if (!this->publicKeyPath.is_complete()) {
        std::stringstream ss;
        ss << "The public key path is invalid : " << this->publicKeyPath.string();
        BOOST_THROW_EXCEPTION(keto::server_common::InvalidPublicKeyDirectoryException(
                ss.str()));
    }
    
    if (!config->getVariablesMap().count(keto::server_common::Constants::ACCOUNT_HASH)) {
        BOOST_THROW_EXCEPTION(keto::server_common::NoServerAccountConfiguredException());
    }
    std::string accountHash = 
            config->getVariablesMap()[keto::server_common::Constants::ACCOUNT_HASH].as<std::string>();
    
    this->accountHash = Botan::hex_decode(accountHash,true);
}

ServerInfo::~ServerInfo() {
}

std::shared_ptr<ServerInfo> ServerInfo::getInstance() {
    std::lock_guard<std::mutex> guard(singletonMutex);
    if (!singleton) {
        singleton = std::shared_ptr<ServerInfo>(new ServerInfo());
    }
    return singleton;
}

std::vector<uint8_t> ServerInfo::getAccountHash() {
    return this->accountHash;
}
    
boost::filesystem::path ServerInfo::getPublicKeyPath() {
    return this->publicKeyPath;
}

}
}
