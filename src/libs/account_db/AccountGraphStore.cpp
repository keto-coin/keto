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

namespace keto {
namespace account_db {

AccountGraphStore::AccountGraphStore(const std::string& dbName) {
    // setup the world
    world = librdf_new_world();
    librdf_world_open(world);
    
    // setup the bdb hash db
    std::shared_ptr<keto::environment::Config> config = 
            keto::environment::EnvironmentManager::getInstance()->getConfig();
    if (!config->getVariablesMap().count(dbName)) {
        std::stringstream ss;
        ss << "The db name supplied is not configured : " << dbName;
        BOOST_THROW_EXCEPTION(keto::account_db::AccountsInvalidDBNameException(
            ss.str()));
    }
    
    boost::filesystem::path dbPath =  
        keto::environment::EnvironmentManager::getInstance()->getEnv()->getInstallDir() / 
        config->getVariablesMap()[dbName].as<std::string>();
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


}
}
