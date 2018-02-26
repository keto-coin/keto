/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Exception.hpp
 * Author: ubuntu
 *
 * Created on February 26, 2018, 1:23 PM
 */

#ifndef KETO_TRANSACTION_EXCEPTION_HPP
#define KETO_TRANSACTION_EXCEPTION_HPP

#include <string>
#include "keto/common/Exception.hpp"


namespace keto {
namespace transaction {
    
// the keto crypto exception base
KETO_DECLARE_EXCEPTION( TransactionServiceException, "Keto Transaction Service Exception." );

// the 
KETO_DECLARE_DERIVED_EXCEPTION (TransactionServiceException, DuplicateTransactionException , "Duplicate transaction for this thread.");
KETO_DECLARE_DERIVED_EXCEPTION (TransactionServiceException, NoTransactionException , "No transaction exists for this thread.");



}
}

#endif /* EXCEPTION_HPP */

