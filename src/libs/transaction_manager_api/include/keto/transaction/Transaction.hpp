/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Transaction.hpp
 * Author: ubuntu
 *
 * Created on February 25, 2018, 11:47 AM
 */

#ifndef KETO_MEMORY_TRANSACTION_HPP
#define KETO_MEMORY_TRANSACTION_HPP

#include <memory>

namespace keto {
namespace transaction {

class Transaction;
typedef std::shared_ptr<Transaction> TransactionPtr;
    
class Transaction {
public:
    virtual void commit() = 0;
    virtual void rollback() = 0;
};

}
}


#endif /* TRANSACTION_HPP */

