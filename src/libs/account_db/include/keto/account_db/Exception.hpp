/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Exception.hpp
 * Author: ubuntu
 *
 * Created on February 21, 2018, 8:16 AM
 */

#ifndef ACCOUNTS_DB_EXCEPTION_HPP
#define ACCOUNTS_DB_EXCEPTION_HPP

#include <string>
#include "keto/common/Exception.hpp"

namespace keto {
namespace account_db {

// the keto db
KETO_DECLARE_EXCEPTION( AccountsDBException, "Accounts DB Exception." );

KETO_DECLARE_DERIVED_EXCEPTION (AccountsDBException, AccountsInvalidDBNameException , "The accounts db could not be founds.");
KETO_DECLARE_DERIVED_EXCEPTION (AccountsDBException, AccountDBInitFailureException , "Could not init the accounts db.");
KETO_DECLARE_DERIVED_EXCEPTION (AccountsDBException, DuplicateGraphDBException , "A graph db exists by this name.");
KETO_DECLARE_DERIVED_EXCEPTION (AccountsDBException, UnsupportedChangeTypeFormatException , "Unsupported type change.");
KETO_DECLARE_DERIVED_EXCEPTION (AccountsDBException, InvalidAccountOperationException , "The operation on the account is invalid.");
KETO_DECLARE_DERIVED_EXCEPTION (AccountsDBException, InvalidParentAccountException , "Parent account was not found.");
KETO_DECLARE_DERIVED_EXCEPTION (AccountsDBException, FailedToInitGraphTransactionException , "Failed to init a graph transaction.");
KETO_DECLARE_DERIVED_EXCEPTION (AccountsDBException, FailedToCommitGraphTransactionException , "Failed to rollback a graph transaction.");
KETO_DECLARE_DERIVED_EXCEPTION (AccountsDBException, FailedToRollbackGraphTransactionException , "Failed to rollback a graph transaction.");
KETO_DECLARE_DERIVED_EXCEPTION (AccountsDBException, UnsupportedDataTypeTransactionException , "Failed to rollback a graph transaction.");
KETO_DECLARE_DERIVED_EXCEPTION (AccountsDBException, UnknownContractException , "The contract was not found to execute.");

}
}


#endif /* EXCEPTION_HPP */

