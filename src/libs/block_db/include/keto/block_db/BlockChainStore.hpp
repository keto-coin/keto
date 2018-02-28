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

#include "SignedBlock.h"

#include "keto/block_db/DBManager.hpp"


namespace keto {
namespace block_db {

class BlockChainStore {
public:
    BlockChainStore();
    BlockChainStore(const BlockChainStore& orig) = delete;
    virtual ~BlockChainStore();
    
    static std::shared_ptr<BlockChainStore> init();
    static void fin();
    static std::shared_ptr<BlockChainStore> getInstance();
    
    
    void writeBlock(const SignedBlock& signedBlock);
    
private:
    std::shared_ptr<DBManager> dbManagerPtr;

};


}
}


#endif /* BLOCKCHAINSTORE_HPP */

