/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RouterRegistry.cpp
 * Author: ubuntu
 * 
 * Created on March 30, 2018, 10:07 AM
 */

#include <map>
#include <set>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <sstream>
#include <mutex>
#include <random>
#include <chrono>

#include "keto/router/RouterRegistry.hpp"
#include "keto/router/Exception.hpp"
#include "keto/server_common/ServerInfo.hpp"

namespace keto {
namespace router {

static RouterRegistryPtr singleton; 
    
RouterRegistry::RouterRegistry() {
}

RouterRegistry::~RouterRegistry() {
}

RouterRegistryPtr RouterRegistry::init() {
    return singleton = std::make_shared<RouterRegistry>();
}

// singleton methods
RouterRegistryPtr RouterRegistry::getInstance() {
    return singleton;
}

void  RouterRegistry::fin() {
    singleton.reset();
}

void RouterRegistry::registerService(const AccountHashVector& accountHash, const std::string& service) {
    std::lock_guard<std::mutex> guard(this->classMutex);
    if (!this->accountServiceMap.count(accountHash)) {
        this->accountServiceMap[accountHash] = std::set<std::string>({service});
    } else {
        this->accountServiceMap[accountHash].insert(service);
    }
    if (!this->serviceAccountMap.count(service)) {
        this->serviceAccountMap[service] = std::set<AccountHashVector>({accountHash});
    } else {
        this->serviceAccountMap[service].insert(accountHash);
    }
}

void RouterRegistry::registerServices(const AccountHashVector& accountHash, const std::vector<std::string>& services) {
    std::lock_guard<std::mutex> guard(this->classMutex);
    std::set<std::string> serviceSet(services.begin(),services.end());
    this->accountServiceMap[accountHash] = serviceSet;
    for (std::map<std::string,std::set<AccountHashVector>>::iterator iter = serviceAccountMap.begin();
            iter != serviceAccountMap.begin(); iter++) {
        if (serviceSet.count(iter->first)) {
            iter->second.insert(accountHash);
        } else {
            iter->second.erase(accountHash);
        }
    }
}

std::vector<std::string> RouterRegistry::getServices(const std::vector<uint8_t>& accountHash) {
    std::lock_guard<std::mutex> guard(this->classMutex);
    std::set<std::string> serviceSet = this->accountServiceMap[accountHash];
    return std::vector<std::string>(serviceSet.begin(),serviceSet.end());
}


AccountHashVector RouterRegistry::getAccount(const std::string& service) {
    std::lock_guard<std::mutex> guard(this->classMutex);
    if (this->serviceAccountMap.count(service)) {
        std::set<AccountHashVector> accountSet = this->serviceAccountMap[service];
        std::vector<AccountHashVector> accounts(accountSet.begin(),accountSet.end());
        // retrieve the random account to handle this service based on the active
        // services.
        if (!accounts.size()) {
            std::stringstream ss;
            ss << "No registered for the service : " << service;
            BOOST_THROW_EXCEPTION(NoAccountsForServiceException(
                ss.str()));
        }
        // setup the random number generator
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::minstd_rand generator (seed);
        int position = (generator() % accounts.size());
        
        return accounts[position];
    }
    std::stringstream ss;
    ss << "The service [" << service << "] is not registered";
    BOOST_THROW_EXCEPTION(NoAccountsForServiceException(
        ss.str()));
}

bool RouterRegistry::isServiceLocal(const std::string& service) {
    AccountHashVector accountHash = keto::server_common::ServerInfo::getInstance()->getAccountHash();
    std::lock_guard<std::mutex> guard(this->classMutex);
    
    if (!this->accountServiceMap.count(accountHash) || !this->accountServiceMap[accountHash].count(service)) {
        return false;
    }
    return true;
}

bool RouterRegistry::isAccountLocal(const AccountHashVector& accountHash) {
    AccountHashVector serverAccountHash = keto::server_common::ServerInfo::getInstance()->getAccountHash();
    return (serverAccountHash == accountHash);
}


}
}
