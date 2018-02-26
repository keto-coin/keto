/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BlockChainStore.hpp
 * Author: ubuntu
 *
 * Created on February 23, 2018, 10:19 AM
 */

#ifndef BLOCKCHAINSTORE_HPP
#define BLOCKCHAINSTORE_HPP

#include <string>
#include <memory>

#include "keto/block_db/DBManager.h"

namespace keto {
namespace block_db {

class BlockChainStore {
public:
    BlockChainStore();
    BlockChainStore(const BlockChainStore& orig) = delete;
    virtual ~BlockChainStore();
    
    
    
private:
    std::shared_ptr<DBManager> DBManagerPtr;

};


}
}


#endif /* BLOCKCHAINSTORE_HPP */

