/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Exception.hpp
 * Author: ubuntu
 *
 * Created on February 21, 2018, 8:16 AM
 */

#ifndef ACCOUNTS_DB_EXCEPTION_HPP
#define ACCOUNTS_DB_EXCEPTION_HPP

#include <string>
#include "keto/common/Exception.hpp"

namespace keto {
namespace account_db {

// the keto db
KETO_DECLARE_EXCEPTION( AccountsDBException, "Accounts DB Exception." );

KETO_DECLARE_DERIVED_EXCEPTION (AccountsDBException, AccountsInvalidDBNameException , "The accounts db could not be founds.");
KETO_DECLARE_DERIVED_EXCEPTION (AccountsDBException, AccountDBInitFailureException , "Could not init the accounts db.");
    
}
}


#endif /* EXCEPTION_HPP */

