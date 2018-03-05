/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AccountStore.hpp
 * Author: ubuntu
 *
 * Created on March 5, 2018, 6:02 AM
 */

#ifndef ACCOUNTSTORE_HPP
#define ACCOUNTSTORE_HPP

#include "keto/rocks_db/DBManager.hpp"
#include "keto/account_db/AccountResourceManager.hpp"

namespace keto {
namespace account_db {


class AccountStore {
public:
    AccountStore(const AccountStore& orig) = delete;
    virtual ~AccountStore();
    
    static std::shared_ptr<AccountStore> init();
    static void fin();
    static std::shared_ptr<AccountStore> getInstance();
    
    
private:
    std::shared_ptr<keto::rocks_db::DBManager> dbManagerPtr;
    AccountResourceManagerPtr accountResourceManagerPtr;

    AccountStore();
    
};


}
}

#endif /* ACCOUNTSTORE_HPP */

