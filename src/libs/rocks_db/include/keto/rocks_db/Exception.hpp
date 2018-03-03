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

#ifndef KETO_ROCKS_DB_EXCEPTION_HPP
#define KETO_ROCKS_DB_EXCEPTION_HPP

#include <string>
#include "keto/common/Exception.hpp"

namespace keto {
namespace rocks_db {

// the keto db
KETO_DECLARE_EXCEPTION( RocksDBException, "DB Exception." );

KETO_DECLARE_DERIVED_EXCEPTION (RocksDBException, RocksDBConnectionException , "Failed to connect to the database.");
KETO_DECLARE_DERIVED_EXCEPTION (RocksDBException, RocksInvalidDBNameException , "The db name supplied is not configured.");

    
}
}


#endif /* EXCEPTION_HPP */

