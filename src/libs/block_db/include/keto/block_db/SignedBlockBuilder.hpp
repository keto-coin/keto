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

#include "keto/block_db/BlockBuilder.hpp"

namespace keto {
namespace block_db {

class SignedBlockBuilder;
typedef std::shared_ptr<SignedBlockBuilder> SignedBlockBuilderPtr;

class SignedBlockBuilder {
public:
    SignedBlockBuilder();
    
    SignedBlockBuilder(const SignedBlockBuilder& orig) = delete;
    virtual ~SignedBlockBuilder();
    
    
private:

};


}
}

#endif /* SIGNEDBLOCKBUILDER_HPP */

