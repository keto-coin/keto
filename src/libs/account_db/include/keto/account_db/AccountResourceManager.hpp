/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AccountResourceManager.hpp
 * Author: ubuntu
 *
 * Created on February 28, 2018, 11:01 AM
 */

#ifndef BLOCKRESOURCEMANAGER_HPP
#define BLOCKRESOURCEMANAGER_HPP

#include <string>
#include <memory>

#include "keto/transaction/Resource.hpp"

#include "keto/rocks_db/DBManager.hpp"
#include "keto/account_db/AccountResource.hpp"
#include "keto/account_db/AccountGraphStoreManager.hpp"


namespace keto {
namespace account_db {

class AccountResourceManager;
typedef std::shared_ptr<AccountResourceManager> AccountResourceManagerPtr;

    
class AccountResourceManager : keto::transaction::Resource {
public:
    AccountResourceManager(std::shared_ptr<keto::rocks_db::DBManager> dbManagerPtr,
            const AccountGraphStoreManagerPtr& accountGraphStoreManagerPtr);
    AccountResourceManager(const AccountResourceManager& orig) = delete;
    virtual ~AccountResourceManager();
    
    virtual void commit();
    virtual void rollback();
    
    AccountResourcePtr getResource();
    
private:
    static thread_local AccountResourcePtr accountResourcePtr;
    std::shared_ptr<keto::rocks_db::DBManager> dbManagerPtr;
    AccountGraphStoreManagerPtr accountGraphStoreManagerPtr;
};


}
}

#endif /* BLOCKRESOURCEMANAGER_HPP */

