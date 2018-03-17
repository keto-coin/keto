/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BlockBuilder.hpp
 * Author: ubuntu
 *
 * Created on March 13, 2018, 3:13 AM
 */

#ifndef BLOCKBUILDER_HPP
#define BLOCKBUILDER_HPP

#include <string>
#include <vector>
#include <memory>

#include "SignedTransaction.h"
#include "SignedChangeSet.h"
#include "TransactionMessage.h"
#include "Block.h"

#include "keto/asn1/TimeHelper.hpp"
#include "keto/asn1/HashHelper.hpp"


namespace keto {
namespace block_db {

class BlockBuilder;
typedef std::shared_ptr<BlockBuilder> BlockBuilderPtr;

class BlockBuilder {
public:
    BlockBuilder();
    BlockBuilder(const keto::asn1::HashHelper& parentHash);
    BlockBuilder(const BlockBuilder& orig) = delete;
    virtual ~BlockBuilder();
    
    
    BlockBuilder& addTransactionMessage(
            const TransactionMessage* transaction);
    
    operator Block_t*();
    operator Block_t&();
    
    
    
private:
    Block_t* block;
    
    
    
    

};


}
}

#endif /* BLOCKBUILDER_HPP */

