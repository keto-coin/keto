/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SignedBlockBuilder.hpp
 * Author: ubuntu
 *
 * Created on March 14, 2018, 2:51 PM
 */

#ifndef SIGNEDBLOCKBUILDER_HPP
#define SIGNEDBLOCKBUILDER_HPP

#include <string>
#include <memory>

#include "Block.h"
#include "SignedBlock.h"

#include "keto/asn1/PrivateKeyHelper.hpp"
#include "keto/block_db/BlockBuilder.hpp"

namespace keto {
namespace block_db {

class SignedBlockBuilder;
typedef std::shared_ptr<SignedBlockBuilder> SignedBlockBuilderPtr;

class SignedBlockBuilder {
public:
    SignedBlockBuilder();
    SignedBlockBuilder(const keto::asn1::PrivateKeyHelper& privateKeyHelper);
    SignedBlockBuilder(Block_t* block,
        const keto::asn1::PrivateKeyHelper& privateKeyHelper);
    
    SignedBlockBuilder(const SignedBlockBuilder& orig) = delete;
    virtual ~SignedBlockBuilder();
    
    SignedBlockBuilder& setPrivateKey(const keto::asn1::PrivateKeyHelper& privateKeyHelper);
    SignedBlockBuilder& setBlock(Block_t* block);
    
    SignedBlockBuilder& sign();
    
    operator SignedBlock_t*();
    operator SignedBlock_t&();
    
private:
    keto::asn1::PrivateKeyHelper privateKeyHelper;
    SignedBlock_t* signedBlock;
    
    keto::asn1::HashHelper getBlockHash(Block_t* block);
};


}
}

#endif /* SIGNEDBLOCKBUILDER_HPP */

