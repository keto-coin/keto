/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TransactionHelper.cpp
 * Author: ubuntu
 * 
 * Created on February 25, 2018, 12:40 PM
 */

#include "keto/module/ModuleManager.hpp"
#include "keto/module/ModuleInterface.hpp"

#include "keto/server_common/TransactionHelper.hpp"

namespace keto {
namespace server_common {

keto::transaction::TransactionPtr createTransaction() {
    return std::dynamic_pointer_cast<keto::transaction::TransactionService>(
            keto::module::ModuleManager::getInstance()->getModule(
            keto::transaction::TransactionService::KETO_TRANSACTION_MANAGER))->createTransaction();
}

void enlistResource(keto::transaction::Resource& resource) {
    std::dynamic_pointer_cast<keto::transaction::TransactionService>(
            keto::module::ModuleManager::getInstance()->getModule(
            keto::transaction::TransactionService::KETO_TRANSACTION_MANAGER))->
            enlistResource(resource);
}

}
}
