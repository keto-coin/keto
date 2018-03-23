/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AccountStatementBuilder.hpp
 * Author: ubuntu
 *
 * Created on March 20, 2018, 11:54 AM
 */

#ifndef ACCOUNTSTATEMENTBUILDER_HPP
#define ACCOUNTSTATEMENTBUILDER_HPP

#include <string>
#include <memory>
#include <vector>

#include <librdf.h>
#include <redland.h>
#include <rdf_storage.h>
#include <rdf_model.h>

#include "ChangeSet.h"

#include "keto/account_db/AccountRDFStatement.hpp"
#include "keto/transaction_common/TransactionMessageHelper.hpp"


namespace keto {
namespace account_db {

class AccountRDFStatementBuilder;
typedef std::shared_ptr<AccountRDFStatementBuilder> AccountRDFStatementBuilderPtr;

class AccountRDFStatementBuilder {
public:
    AccountRDFStatementBuilder(const keto::transaction_common::TransactionMessageHelperPtr& transactionMessageHelper);
    AccountRDFStatementBuilder(const AccountRDFStatementBuilder& orig) = delete;
    virtual ~AccountRDFStatementBuilder();
    
    std::vector<AccountRDFStatementPtr> getStatements();
    
    
private:
    keto::transaction_common::TransactionMessageHelperPtr transactionMessageHelper;
    std::vector<AccountRDFStatementPtr> statements;
};


}
}

#endif /* ACCOUNTSTATEMENTBUILDER_HPP */

