/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TransactionBuilder.cpp
 * Author: brett chaldecott
 * 
 * Created on January 30, 2018, 3:04 PM
 */

#include <memory>
#include <stdlib.h>

#include "keto/chain_common/TransactionBuilder.hpp"
#include "keto/common/MetaInfo.hpp"

namespace keto {
namespace chain_common {


TransactionBuilder::TransactionBuilder() {
    this->transaction = (Transaction*)calloc(1, sizeof *transaction);
    this->transaction->version = keto::common::MetaInfo::PROTOCOL_VERSION;
}

TransactionBuilder::~TransactionBuilder() {
    free(this->transaction);
}

std::shared_ptr<TransactionBuilder> TransactionBuilder::createTransaction() {
    return std::shared_ptr<TransactionBuilder>(new TransactionBuilder());
}


unsigned char* TransactionBuilder::getBytes() {
    return NULL;
}



}
}