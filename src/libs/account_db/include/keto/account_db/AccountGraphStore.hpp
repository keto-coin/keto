/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AccountGraphStore.hpp
 * Author: ubuntu
 *
 * Created on March 5, 2018, 7:30 AM
 */

#ifndef ACCOUNTGRAPHSTORE_HPP
#define ACCOUNTGRAPHSTORE_HPP

#include <memory>

#include <librdf.h>
#include <redland.h>
#include <rdf_storage.h>
#include <rdf_model.h>

namespace keto {
namespace account_db {

class AccountGraphStore;
typedef std::shared_ptr<AccountGraphStore> AccountGraphStorePtr;
    
class AccountGraphStore {
public:
    AccountGraphStore(const std::string& dbName);
    AccountGraphStore(const AccountGraphStore& orig) = delete;
    virtual ~AccountGraphStore();
    
    static bool checkForDb(const std::string& dbName);
    
private:
    librdf_world* world;
    librdf_storage* storage;
    librdf_model* model;
};


}
}


#endif /* ACCOUNTGRAPHSTORE_HPP */

