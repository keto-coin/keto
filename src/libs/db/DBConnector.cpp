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

#include "keto/db/Exception.hpp"
#include "keto/db/DBConnector.hpp"
#include "include/keto/db/DBConnector.hpp"

namespace keto {
namespace db {

DBConnector::DBConnector(const std::string& path) {
    rocksdb::Options options;
    options.create_if_missing = true;
    rocksdb::Status status = rocksdb::DB::Open(options, 
            path, &this->db);
    if (!status.ok()) {
        std::stringstream ss;
        ss << "Failed to connect to the database [" << path << "]" << std::endl;
        BOOST_THROW_EXCEPTION(keto::db::DBConnectionException(
                ss.str()));
    }
}

DBConnector::~DBConnector() {
}




}
}