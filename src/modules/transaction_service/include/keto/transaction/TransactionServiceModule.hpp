/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TransactionServiceModule.hpp
 * Author: ubuntu
 *
 * Created on February 26, 2018, 8:22 AM
 */

#ifndef TRANSACTIONSERVICEMODULE_HPP
#define TRANSACTIONSERVICEMODULE_HPP

#include <string>
#include <map>
#include <memory>

#include "keto/module/ModuleInterface.hpp"
#include "keto/transaction/TransactionService.hpp"

namespace keto {
namespace transaction {


class TransactionServiceModule : public keto::module::ModuleInterface,
    public TransactionService {
public:
    friend class TransactionImpl;
    
    TransactionServiceModule();
    TransactionServiceModule(const TransactionServiceModule& orig) = delete;
    virtual ~TransactionServiceModule();
    
    // meta methods
    virtual const std::string getName() const;
    virtual const std::string getDescription() const;
    virtual const std::string getVersion() const;
    
    // transaction methods
    virtual TransactionPtr createTransaction();
    virtual void enlistResource(Resource& resource);

protected:
    void commit();
    void rollback();
    
private:
    static thread_local TransactionWrapperPtr transactionWrapper;

};


}
}

#endif /* TRANSACTIONSERVICEMODULE_HPP */

