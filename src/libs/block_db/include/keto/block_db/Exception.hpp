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

#ifndef KETO_DB_EXCEPTION_HPP
#define KETO_DB_EXCEPTION_HPP

#include <string>
#include "keto/common/Exception.hpp"

namespace keto {
namespace block_db {

// the keto db
KETO_DECLARE_EXCEPTION( DBException, "DB Exception." );

KETO_DECLARE_DERIVED_EXCEPTION (DBException, DBConnectionException , "Failed to connect to the database.");

    
}
}


#endif /* EXCEPTION_HPP */

