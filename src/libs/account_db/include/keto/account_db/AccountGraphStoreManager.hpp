/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AccountGraphStoreManager.hpp
 * Author: ubuntu
 *
 * Created on March 20, 2018, 7:58 AM
 */

#ifndef ACCOUNTGRAPHSTOREMANAGER_HPP
#define ACCOUNTGRAPHSTOREMANAGER_HPP

#include <string>
#include <memory>
#include <map>

#include "keto/account_db/AccountGraphStore.hpp"

namespace keto {
namespace account_db {

class AccountGraphStoreManager;
typedef std::shared_ptr<AccountGraphStoreManager> AccountGraphStoreManagerPtr;

class AccountGraphStoreManager {
public:
    AccountGraphStoreManager();
    AccountGraphStoreManager(const AccountGraphStoreManager& orig) = delete;
    virtual ~AccountGraphStoreManager();
    
    AccountGraphStorePtr operator[](const std::string& dbName);
    bool checkForDb(const std::string& dbName);
    AccountGraphStorePtr createStore(const std::string& dbName);
    
private:
    std::map<std::string,AccountGraphStorePtr> graphs;
};


}
}

#endif /* ACCOUNTGRAPHSTOREMANAGER_HPP */

