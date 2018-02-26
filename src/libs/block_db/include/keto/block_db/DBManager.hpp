/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DBManager.hpp
 * Author: ubuntu
 *
 * Created on February 23, 2018, 9:43 AM
 */

#ifndef DBMANAGER_HPP
#define DBMANAGER_HPP

#include <map>
#include <vector>
#include <string>
#include <memory>

#include "keto/block_db/DBConnector.hpp"

namespace keto {
namespace block_db {


class DBManager {
public:
    DBManager(const std::vector<std::string>& databases);
    DBManager(const DBManager& orig) = delete;
    virtual ~DBManager();
    
    keto::block_db::DBConnectorPtr getConnection(const std::string& database);
    
    
    
private:
    std::map<std::string,keto::block_db::DBConnectorPtr> connections;
    
    
};


}
}

#endif /* DBMANAGER_HPP */

