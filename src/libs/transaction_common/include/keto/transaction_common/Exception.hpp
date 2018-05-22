/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Exception.hpp
 * Author: Brett Chaldecott
 *
 * Created on January 31, 2018, 4:37 PM
 */

#ifndef TRANSACTION_COMMON_EXCEPTION_HPP
#define TRANSACTION_COMMON_EXCEPTION_HPP

#include <string>
#include "keto/common/Exception.hpp"


namespace keto {
namespace transaction_common {

// the keto environment exception base
KETO_DECLARE_EXCEPTION( TransactionCommonException, "Transaction common exception." );

// the keto environment derived exception
KETO_DECLARE_DERIVED_EXCEPTION (TransactionCommonException, ChangeSequenceAddFailedException , "Failed to add a change to the change set.");
KETO_DECLARE_DERIVED_EXCEPTION (TransactionCommonException, TransactionTraceSequenceAddFailedException , "Failed to add a transaction trace to the sequence.");
KETO_DECLARE_DERIVED_EXCEPTION (TransactionCommonException, SignedChangeSetSequenceAddFailedException , "Failed to add a signed change to the sequence.");
KETO_DECLARE_DERIVED_EXCEPTION (TransactionCommonException, ANYSerializationFailedException , "Failed to serialize object.");
KETO_DECLARE_DERIVED_EXCEPTION (TransactionCommonException, UnrecognisedTransactionStatusException , "The transaction is in an unrecognised state.");

}
}

#endif /* EXCEPTION_HPP */

