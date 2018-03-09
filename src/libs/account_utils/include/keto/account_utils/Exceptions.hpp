/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Exceptions.hpp
 * Author: ubuntu
 *
 * Created on March 9, 2018, 3:21 AM
 */

#ifndef ACCOUNT_UTILS_EXCEPTIONS_HPP
#define ACCOUNT_UTILS_EXCEPTIONS_HPP

#include <string>
#include "keto/common/Exception.hpp"

namespace keto {
namespace account_utils {

// the keto db
KETO_DECLARE_EXCEPTION( AccountUtilsException, "Accounts Utils Exception." );

KETO_DECLARE_DERIVED_EXCEPTION (AccountUtilsException, InvalidPrivateKeyPathException , "The private key path supplied is invalid.");
    
}
}



#endif /* EXCEPTIONS_HPP */

