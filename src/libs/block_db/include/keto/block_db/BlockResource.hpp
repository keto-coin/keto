/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BlockResource.hpp
 * Author: ubuntu
 *
 * Created on February 28, 2018, 10:56 AM
 */

#ifndef BLOCKRESOURCE_HPP
#define BLOCKRESOURCE_HPP

#include <string>
#include <memory>
#include <map>

#include "rocksdb/db.h"
#include "rocksdb/utilities/transaction.h"
#include "rocksdb/utilities/transaction_db.h"

#include "keto/transaction/Resource.hpp"

#include "keto/rocks_db/DBManager.hpp"

namespace keto {
namespace block_db {

class BlockResource;
typedef std::shared_ptr<BlockResource> BlockResourcePtr;

class BlockResource {
public:
    BlockResource(std::shared_ptr<keto::rocks_db::DBManager> dbManagerPtr);
    BlockResource(const BlockResource& orig) = delete;
    virtual ~BlockResource();
    
    void commit();
    void rollback();
    
    
    rocksdb::Transaction* getTransaction(const std::string& name);
    
private:
    std::shared_ptr<keto::rocks_db::DBManager> dbManagerPtr;
    std::map<std::string,rocksdb::Transaction*> transactionMap;
    
};


}
}
#endif /* BLOCKRESOURCE_HPP */

