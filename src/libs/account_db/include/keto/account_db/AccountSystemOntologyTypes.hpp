/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AccountSystemOntologyTypes.hpp
 * Author: ubuntu
 *
 * Created on March 26, 2018, 2:59 AM
 */

#ifndef ACCOUNTSYSTEMONTOLOGYTYPES_HPP
#define ACCOUNTSYSTEMONTOLOGYTYPES_HPP

#include <string>
#include <vector>

#include "keto/asn1/HashHelper.hpp"
#include "keto/asn1/RDFSubjectHelper.hpp"

namespace keto {
namespace account_db {


class AccountSystemOntologyTypes {
public:
    static const char* ACCOUNT_ONTOLOGY_CLASS;
    static const char* ACCOUNT_STATUS_PREDICATE;
    static const char* ACCOUNT_ID_PREDICATE;
    static const char* ACCOUNT_OBJECT_STATUS;
    
    
    static const std::vector<std::string> ONTOLOGY_CLASSES; 
    
    static bool validateClassOperation(
        const keto::asn1::HashHelper& targetAccount,
        const bool existingAccount,
        const keto::asn1::RDFSubjectHelperPtr& accountRDFStatement);
    
private:
    
    
};


}
}
#endif /* ACCOUNTSYSTEMONTOLOGYTYPES_HPP */

