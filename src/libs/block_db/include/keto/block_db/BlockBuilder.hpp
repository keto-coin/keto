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

#include "SignedTransaction.h"
#include "SignedChangeSet.h"
#include "Block.h"

#include "keto/asn1/TimeHelper.hpp"
#include "keto/asn1/HashHelper.hpp"

#include "keto/block_db/SignedChangeSetBuilder.hpp"

namespace keto {
namespace block_db {


class BlockBuilder {
public:
    BlockBuilder();
    BlockBuilder(const keto::asn1::HashHelper& parentHash);
    BlockBuilder(const BlockBuilder& orig) = delete;
    virtual ~BlockBuilder();
    
    
    BlockBuilder& addSignedTransaction(
            const SignedTransaction& transaction);
    BlockBuilder& addChangeSet(
            const SignedChangeSetBuilderPtr& changeSet);
    
    operator Block_t*();
    
    
    
private:
    keto::asn1::TimeHelper date;
    keto::asn1::HashHelper parentHash;
    std::vector<SignedTransaction> transactions;
    std::vector<SignedChangeSetBuilderPtr> changeSets;
    
    
    
    

};


}
}

#endif /* BLOCKBUILDER_HPP */

