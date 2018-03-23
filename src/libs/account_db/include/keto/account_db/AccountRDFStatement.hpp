/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AccountRDFStatement.hpp
 * Author: ubuntu
 *
 * Created on March 21, 2018, 5:50 PM
 */

#ifndef ACCOUNTRDFSTATEMENT_HPP
#define ACCOUNTRDFSTATEMENT_HPP

#include <string>
#include <memory>

#include "ChangeData.h"

#include "keto/asn1/RDFSubjectHelper.hpp"
#include "keto/asn1/RDFModelHelper.hpp"
#include "keto/account_db/RDFDBOperation.hpp"

namespace keto {
namespace account_db {

class AccountRDFStatement;
typedef std::shared_ptr<AccountRDFStatement> AccountRDFStatementPtr;

class AccountRDFStatement {
public:
    AccountRDFStatement(ChangeData* changeData);
    AccountRDFStatement(const AccountRDFStatement& orig) = delete;
    virtual ~AccountRDFStatement();
    
    RDFDBOperation getOperation();
    keto::asn1::RDFModelHelperPtr getModel();
    
    
    
private:
    keto::asn1::RDFModelHelperPtr rdfModelHelper;
    
};


}
}

#endif /* ACCOUNTRDFSTATEMENT_HPP */

