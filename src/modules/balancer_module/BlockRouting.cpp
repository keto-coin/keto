/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BlockRouting.cpp
 * Author: ubuntu
 * 
 * Created on March 31, 2018, 4:25 PM
 */

#include "keto/environment/EnvironmentManager.hpp"
#include "keto/environment/Config.hpp"

#include "keto/balancer/BlockRouting.hpp"
#include "keto/balancer/Constants.hpp"
#include "keto/server_common/ServerInfo.hpp"
#include "include/keto/balancer/BlockRouting.hpp"


namespace keto {
namespace balancer {

static BlockRoutingPtr singleton;

BlockRouting::BlockRouting() {
    // retrieve the configuration
    std::shared_ptr<keto::environment::Config> config = 
            keto::environment::EnvironmentManager::getInstance()->getConfig();
    
    // retrieve the host information from the configuration file
    if (config->getVariablesMap().count(Constants::DEFAULT_BLOCK) && 
            config->getVariablesMap()[Constants::DEFAULT_BLOCK].as<std::string>().compare("true") == 0) {
        this->accounts.push_back(keto::server_common::ServerInfo::getInstance()->getAccountHash());
    }
}

BlockRouting::~BlockRouting() {
}

//void set
BlockRoutingPtr BlockRouting::init() {
    return singleton = std::make_shared<BlockRouting>();
}
    
BlockRoutingPtr BlockRouting::getInstance() {
    return singleton;
}

void BlockRouting::fin() {
    singleton.reset();
}
    

std::vector<AccountHashVector> BlockRouting::getBlockAccounts() {
    return this->accounts;
}

void BlockRouting::setBlockAccounts(const std::vector<AccountHashVector>& accounts) {
    std::lock_guard<std::mutex> guard(this->classMutex);
    this->accounts = accounts;
}


}
}