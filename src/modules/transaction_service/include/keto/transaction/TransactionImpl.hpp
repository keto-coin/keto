/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TransactionImpl.hpp
 * Author: ubuntu
 *
 * Created on February 26, 2018, 1:06 PM
 */

#ifndef KETO_TRANSACTIONIMPL_HPP
#define KETO_TRANSACTIONIMPL_HPP

#include "keto/transaction/Transaction.hpp"
#include "keto/transaction/TransactionService.hpp"

namespace keto {
namespace transaction {

class TransactionServiceModule;
    
class TransactionImpl : public Transaction {
public:
    TransactionImpl(TransactionServiceModule& transactionService);
    TransactionImpl(const TransactionImpl& orig) = delete;
    virtual ~TransactionImpl();
    
    virtual void commit();
    virtual void rollback();
    
private:
    TransactionServiceModule& transactionService;
    bool complete;
    
};


}
}


#endif /* TRANSACTIONIMPL_HPP */

