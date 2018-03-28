/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AccountGraphStore.cpp
 * Author: ubuntu
 * 
 * Created on March 5, 2018, 7:30 AM
 */

#include <sstream>
#include <iostream>

#include <boost/filesystem/path.hpp>

#include "keto/account_db/AccountGraphStore.hpp"
#include "keto/account_db/Exception.hpp"

#include "keto/environment/EnvironmentManager.hpp"
#include "keto/environment/Config.hpp"
#include "include/keto/account_db/Constants.hpp"

namespace keto {
namespace account_db {

AccountGraphStore::AccountGraphStore(const std::string& dbName) : dbName(dbName) {
    // setup the world
    world = librdf_new_world();
    librdf_world_open(world);
    
    
    // setup the bdb hash db
    std::shared_ptr<keto::environment::Config> config = 
            keto::environment::EnvironmentManager::getInstance()->getConfig();
    if (!config->getVariablesMap().count(Constants::GRAPH_BASE_DIR)) {
        std::stringstream ss;
        ss << "The graph db base directory is not configured : " << Constants::GRAPH_BASE_DIR;
        BOOST_THROW_EXCEPTION(keto::account_db::AccountsInvalidDBNameException(
            ss.str()));
    }
    
    // create a db directory
    boost::filesystem::path graphBaseDir =  
        keto::environment::EnvironmentManager::getInstance()->getEnv()->getInstallDir() / 
        config->getVariablesMap()[Constants::GRAPH_BASE_DIR].as<std::string>();
    
    if (!boost::filesystem::exists(graphBaseDir)) {
        boost::filesystem::create_directory(graphBaseDir);
    }    
    
    boost::filesystem::path dbPath =  graphBaseDir / 
        dbName;
    if (!boost::filesystem::exists(dbPath)) {
        boost::filesystem::create_directory(dbPath);
    }
    std::stringstream ss;
    ss << "hash-type='bdb',dir='" << dbPath.c_str() << "'" ;
    storage=librdf_new_storage(world, "hashes", dbName.c_str(),
                             ss.str().c_str());
    model = librdf_new_model(world,storage,NULL);
    if (!storage || !model) {
        BOOST_THROW_EXCEPTION(keto::account_db::AccountDBInitFailureException());
    }
    
}

AccountGraphStore::~AccountGraphStore() {
    librdf_free_model(model);
    librdf_free_storage(storage);
    librdf_free_world(world);
}


std::string AccountGraphStore::getDbName() {
    return this->dbName;
}


bool AccountGraphStore::checkForDb(const std::string& dbName) {
    std::shared_ptr<keto::environment::Config> config = 
            keto::environment::EnvironmentManager::getInstance()->getConfig();
    if (!config->getVariablesMap().count(Constants::GRAPH_BASE_DIR)) {
        std::stringstream ss;
        ss << "The graph db base directory is not configured : " << Constants::GRAPH_BASE_DIR;
        BOOST_THROW_EXCEPTION(keto::account_db::AccountsInvalidDBNameException(
            ss.str()));
    }
    
    // create a db directory
    boost::filesystem::path graphBaseDir =  
        keto::environment::EnvironmentManager::getInstance()->getEnv()->getInstallDir() / 
        config->getVariablesMap()[Constants::GRAPH_BASE_DIR].as<std::string>();
    
    if (!boost::filesystem::exists(graphBaseDir)) {
        return false;
    }    
    
    boost::filesystem::path dbPath =  graphBaseDir / 
        dbName;
    if (!boost::filesystem::exists(dbPath)) {
        return false;
    }
    return true;
}


librdf_world* AccountGraphStore::getWorld() {
    return this->world;
}

librdf_storage* AccountGraphStore::getStorage() {
    return this->storage;
}

librdf_model* AccountGraphStore::getModel() {
    return this->model;
}

}
}
