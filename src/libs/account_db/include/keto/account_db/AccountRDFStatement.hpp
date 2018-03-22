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

#include "keto/asn1/RDFSubjectHelper.hpp"
#include "keto/account_db/RDFDBOperation.hpp"

namespace keto {
namespace account_db {

class AccountRDFStatement;
typedef 

class AccountRDFStatement {
public:
    AccountRDFStatement(const RDFSubject* subject);
    AccountRDFStatement(const AccountRDFStatement& orig);
    virtual ~AccountRDFStatement();
    
    RDFDBOperation getOperation();
    keto::asn1::RDFSubjectHelper getSubject();
    
    
    
private:
    RDFDBOperation operation;
    keto::asn1::RDFSubjectHelper rdfSubjectHelper;
    
};


}
}

#endif /* ACCOUNTRDFSTATEMENT_HPP */

