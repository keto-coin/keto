/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TransactionWrapper.hpp
 * Author: ubuntu
 *
 * Created on February 26, 2018, 12:53 PM
 */

#ifndef KETO_TRANSACTIONWRAPPER_HPP
#define KETO_TRANSACTIONWRAPPER_HPP

#include <memory>
#include <string>
#include <vector>

#include "keto/transaction/Resource.hpp"

namespace keto {
namespace transaction {

class TransactionWrapper;
typedef std::shared_ptr<TransactionWrapper> TransactionWrapperPtr;

class TransactionWrapper {
public:
    TransactionWrapper();
    TransactionWrapper(const TransactionWrapper& orig) = delete;
    virtual ~TransactionWrapper();
    
    void commit();
    void rollback();
    
    void enlist(Resource& resource);
    
private:
    std::vector<Resource*> resources;
};


}
}

#endif /* TRANSACTIONWRAPPER_HPP */

