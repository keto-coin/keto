/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AccountResource.hpp
 * Author: ubuntu
 *
 * Created on February 28, 2018, 10:56 AM
 */

#ifndef ACCOUNT_RESOURCE_HPP
#define ACCOUNT_RESOURCE_HPP

#include <string>
#include <memory>
#include <map>

#include "rocksdb/db.h"
#include "rocksdb/utilities/transaction.h"
#include "rocksdb/utilities/transaction_db.h"

#include "keto/transaction/Resource.hpp"

#include "keto/rocks_db/DBManager.hpp"

namespace keto {
namespace account_db {

class AccountResource;
typedef std::shared_ptr<AccountResource> AccountResourcePtr;

class AccountResource {
public:
    AccountResource(std::shared_ptr<keto::rocks_db::DBManager> dbManagerPtr);
    AccountResource(const AccountResource& orig) = delete;
    virtual ~AccountResource();
    
    void commit();
    void rollback();
    
    
    rocksdb::Transaction* getTransaction(const std::string& name);
    
private:
    std::shared_ptr<keto::rocks_db::DBManager> dbManagerPtr;
    std::map<std::string,rocksdb::Transaction*> transactionMap;
    
};


}
}
#endif /* ACCOUNT_RESOURCE_HPP */

