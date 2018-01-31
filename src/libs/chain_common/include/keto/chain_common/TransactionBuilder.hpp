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

#include "Transaction.h"

namespace keto {
namespace chain_common {


class TransactionBuilder {
public:
    TransactionBuilder(const TransactionBuilder& orig) = delete;
    virtual ~TransactionBuilder();
    
    static std::shared_ptr<TransactionBuilder> createTransaction();
    
    std::vector<unsigned char> getBytes();
private:
    Transaction* transaction;
    
    TransactionBuilder();
    
};

}
}


#endif /* TRANSACTIONBUILDER_HPP */

