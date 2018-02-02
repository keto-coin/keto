/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TransactionBuilder.hpp
 * Author: ubuntu
 *
 * Created on January 30, 2018, 3:04 PM
 */

#ifndef TRANSACTIONBUILDER_HPP
#define TRANSACTIONBUILDER_HPP

#include <memory>
#include <vector>
#include <iostream>
#include <cerrno>
#include <cstring>

#include "Transaction.h"
#include "keto/asn1/SerializationHelper.hpp"
#include "keto/asn1/NumberHelper.hpp"

namespace keto {
namespace chain_common {


class TransactionBuilder {
public:
    TransactionBuilder(const TransactionBuilder& orig) = delete;
    virtual ~TransactionBuilder();
    
    static std::shared_ptr<TransactionBuilder> createTransaction();
    
    TransactionBuilder& setValue(const keto::asn1::NumberHelper& numberHelper);
    keto::asn1::NumberHelper getValue();
    
    operator std::vector<uint8_t>&();
    
    operator uint8_t*();
    
    size_t size();
    
    
private:
    Transaction* transaction;
    std::shared_ptr<keto::asn1::SerializationHelper<Transaction>> serializationHelperPtr;
    
    TransactionBuilder();
    
    void serializeTransaction();
    
};

}
}


#endif /* TRANSACTIONBUILDER_HPP */

