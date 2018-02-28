/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BlockChainStore.cpp
 * Author: ubuntu
 * 
 * Created on February 23, 2018, 10:19 AM
 */

#include "keto/block_db/BlockChainStore.hpp"
#include "keto/block_db/DBManager.hpp"
#include "keto/block_db/Constants.hpp"
#include "keto/server_common/TransactionHelper.hpp"

namespace keto {
namespace block_db {

static std::shared_ptr<BlockChainStore> singleton;
    
BlockChainStore::BlockChainStore() {
    dbManagerPtr = std::shared_ptr<DBManager>(new DBManager(Constants::DB_LIST));
}

BlockChainStore::~BlockChainStore() {
    dbManagerPtr.reset();
}

std::shared_ptr<BlockChainStore> BlockChainStore::init() {
    if (singleton) {
        return singleton;
    }
    return singleton = std::shared_ptr<BlockChainStore>(new BlockChainStore());
}

void BlockChainStore::fin() {
    singleton.reset();
}

std::shared_ptr<BlockChainStore> BlockChainStore::getInstance() {
    return singleton;
}


void BlockChainStore::writeBlock(const SignedBlock& signedBlock) {
    dbManagerPtr->getConnection(Constants::BLOCKS_INDEX)->getDB();
}



}
}
