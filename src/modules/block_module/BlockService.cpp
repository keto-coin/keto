/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BlockService.cpp
 * Author: ubuntu
 * 
 * Created on March 8, 2018, 3:04 AM
 */

#include <condition_variable>

#include "keto/block/BlockService.hpp"
#include "keto/block_db/BlockChainStore.hpp"

namespace keto {
namespace block {

static std::shared_ptr<BlockService> singleton;


BlockService::BlockService() {
}

BlockService::~BlockService() {
}

std::shared_ptr<BlockService> BlockService::init() {
    if (singleton) {
        singleton = std::shared_ptr<BlockService>(new BlockService());
    }
    return singleton;
}

void BlockService::fin() {
    singleton.reset();
}

std::shared_ptr<BlockService> BlockService::getInstance() {
    return singleton;
}

void BlockService::boot() {
    if (keto::block_db::BlockChainStore::getInstance()->requireBoot()) {
        
    }
}

}
}