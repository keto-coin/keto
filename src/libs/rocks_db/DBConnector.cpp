/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DBConnector.cpp
 * Author: ubuntu
 * 
 * Created on February 21, 2018, 6:54 AM
 */

#include <sstream>
#include <iostream>


#include "keto/rocks_db/Exception.hpp"
#include "keto/rocks_db/DBConnector.hpp"

namespace keto {
namespace rocks_db {

DBConnector::DBConnector(const std::string& path) : db(NULL) {
    options.create_if_missing = true;
    
    rocksdb::Status status = rocksdb::TransactionDB::Open(options, 
            txn_db_options,path, &db);
    if (!status.ok()) {
        std::stringstream ss;
        ss << "Failed to connect to the database [" << path << "]" << std::endl;
        BOOST_THROW_EXCEPTION(keto::rocks_db::RocksDBConnectionException(
                ss.str()));
    }
}

DBConnector::~DBConnector() {
    delete db;
}


rocksdb::TransactionDB* DBConnector::getDB() {
    
    return this->db;
}



}
}