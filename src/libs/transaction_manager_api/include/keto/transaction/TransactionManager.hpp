/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TransactionManager.hpp
 * Author: ubuntu
 *
 * Created on February 25, 2018, 12:32 PM
 */

#ifndef TRANSACTIONMANAGER_HPP
#define TRANSACTIONMANAGER_HPP

#include "keto/transaction/Transaction.hpp"
#include "keto/transaction/Resource.hpp"

namespace keto {
namespace transaction {

class TransactionManager {
public:
    static constexpr const char* KETO_TRANSACTION_MANAGER = "transaction_manager";
    
    virtual TransactionPtr createTransaction() = 0;
    
    virtual void enlistResource(Resource& resource) = 0;
};

}
}

#endif /* TRANSACTIONMANAGER_HPP */

