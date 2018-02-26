/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TransactionServiceModuleManager.hpp
 * Author: ubuntu
 *
 * Created on February 26, 2018, 2:17 PM
 */

#ifndef TRANSACTIONSERVICEMODULEMANAGER_HPP
#define TRANSACTIONSERVICEMODULEMANAGER_HPP

#include "keto/module/ModuleManagementInterface.hpp"
#include "keto/transaction/TransactionServiceModule.hpp"

namespace keto {
namespace transaction {


class TransactionServiceModuleManager : public keto::module::ModuleManagementInterface {
public:
    TransactionServiceModuleManager();
    TransactionServiceModuleManager(const TransactionServiceModuleManager& orig) = delete;
    virtual ~TransactionServiceModuleManager();
    
    // meta methods
    virtual const std::string getName() const;
    virtual const std::string getDescription() const;
    virtual const std::string getVersion() const;
    
    // lifecycle methods
    virtual void start();
    virtual void stop();
    
    virtual const std::vector<std::string> listModules();
    virtual const std::shared_ptr<keto::module::ModuleInterface> getModule(const std::string& name);
    
    static boost::shared_ptr<TransactionServiceModuleManager> create_module();
    
private:
    std::map<std::string,std::shared_ptr<keto::module::ModuleInterface>> modules;
};


}
}

#endif /* TRANSACTIONSERVICEMODULEMANAGER_HPP */

