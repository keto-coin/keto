/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BlockBuilder.cpp
 * Author: ubuntu
 * 
 * Created on March 13, 2018, 3:13 AM
 */

#include <vector>

#include "keto/common/MetaInfo.hpp"
#include "keto/block_db/BlockBuilder.hpp"
#include "keto/block_db/Exception.hpp"
#include "keto/block_db/MerkleUtils.hpp"
#include "keto/block_db/SignedChangeSetBuilder.hpp"
#include "keto/block_db/MerkleUtils.hpp"

namespace keto {
namespace block_db {

BlockBuilder::BlockBuilder() {
}


BlockBuilder::BlockBuilder(const keto::asn1::HashHelper& parentHash) :
    parentHash(parentHash) {    
}
    

BlockBuilder::~BlockBuilder() {
}

BlockBuilder& BlockBuilder::addSignedTransaction(
        const SignedTransaction& transaction) {
    transactions.push_back(transaction);
    return (*this);
}

BlockBuilder& BlockBuilder::addChangeSet(
        const SignedChangeSetBuilderPtr& changeSet) {
    changeSets.push_back(changeSet);
    return (*this);
}

BlockBuilder::operator Block_t*() {
    Block_t* block = (Block_t*)calloc(1, sizeof *block);
    block->version = keto::common::MetaInfo::PROTOCOL_VERSION;
    block->date = this->date;
    block->parent = this->parentHash;
    
    MerkleUtils merkleUtils(this->transactions,this->changeSets);
    
    for (SignedTransaction& signedTransaction : this->transactions) {
        if (0!= ASN_SEQUENCE_ADD(&block->transactions,new SignedTransaction(signedTransaction))) {
            ASN_STRUCT_FREE(asn_DEF_Block, block);
            BOOST_THROW_EXCEPTION(keto::block_db::FailedToAddTheTransactionException());
        }
    }
    for (SignedChangeSetBuilderPtr signedChangeSetBuilder : this->changeSets) {
        if (0!= ASN_SEQUENCE_ADD(&block->changeSet,signedChangeSetBuilder->operator SignedChangeSet_t*())) {
            ASN_STRUCT_FREE(asn_DEF_Block, block);
            BOOST_THROW_EXCEPTION(keto::block_db::FailedToAddTheTransactionException());
        }
    }
    block->merkelRoot = merkleUtils.computation();
    
    return block;
}



}
}
