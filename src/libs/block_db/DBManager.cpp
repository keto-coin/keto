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

#include "keto/block_db/DBManager.hpp"

namespace keto {
namespace block_db {

DBManager::DBManager(const std::vector<std::string>& databases) {
}

DBManager::~DBManager() {
}

keto::block_db::DBConnectorPtr DBManager::getConnection(const std::string& name) {
    return connections[name];
}

}
}
