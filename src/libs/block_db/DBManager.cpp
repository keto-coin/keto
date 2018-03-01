/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DBManager.cpp
 * Author: ubuntu
 * 
 * Created on February 23, 2018, 9:43 AM
 */

#include <iostream>
#include <sstream>

#include <boost/filesystem/path.hpp>

#include "keto/block_db/DBManager.hpp"
#include "keto/block_db/Exception.hpp"

#include "keto/environment/EnvironmentManager.hpp"
#include "keto/environment/Config.hpp"


namespace keto {
namespace block_db {

DBManager::DBManager(const std::vector<std::string>& databases) {
    std::shared_ptr<keto::environment::Config> config = 
            keto::environment::EnvironmentManager::getInstance()->getConfig();
    for (std::string dbName : databases) {
        if (!config->getVariablesMap().count(dbName)) {
            std::stringstream ss;
            ss << "The db name supplied is not configured : " << dbName;
            BOOST_THROW_EXCEPTION(keto::block_db::InvalidDBNameException(
                ss.str()));
        }
        
        boost::filesystem::path dbPath =  
                keto::environment::EnvironmentManager::getInstance()->getEnv()->getInstallDir() / 
                config->getVariablesMap()[dbName].as<std::string>();
        connections[dbName] = DBConnectorPtr(new DBConnector(dbPath.c_str()));
    }
}

DBManager::~DBManager() {
    connections.clear();
}

keto::block_db::DBConnectorPtr DBManager::getConnection(const std::string& name) {
    return connections[name];
}


}
}
