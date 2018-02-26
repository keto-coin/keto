/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TransactionHelper.hpp
 * Author: ubuntu
 *
 * Created on February 25, 2018, 12:40 PM
 */

#ifndef TRANSACTIONHELPER_HPP
#define TRANSACTIONHELPER_HPP

#include "keto/transaction/Transaction.hpp"
#include "keto/transaction/Resource.hpp"
#include "keto/transaction/TransactionService.hpp"

namespace keto {
namespace server_common {

keto::transaction::TransactionPtr createTransaction();   

void enlistResource(keto::transaction::Resource& resource);

}
}

#endif /* TRANSACTIONHELPER_HPP */

