/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RDFModelHelper.hpp
 * Author: ubuntu
 *
 * Created on March 11, 2018, 12:24 PM
 */

#ifndef RDFSUBJECTHELPER_HPP
#define RDFSUBJECTHELPER_HPP

#include <string>
#include <vector>
#include <memory>

#include "RDFSubject.h"
#include "ANY.h"

#include "keto/asn1/RDFPredicateHelper.hpp"

namespace keto {
namespace asn1 {

class RDFSubjectHelper;
typedef std::shared_ptr<RDFSubjectHelper> RDFSubjectHelperPtr;

class RDFSubjectHelper {
public:
    RDFSubjectHelper();
    RDFSubjectHelper(RDFSubject_t* subject);
    RDFSubjectHelper(RDFSubject_t* subject, bool own);
    RDFSubjectHelper(const std::string& subject);
    RDFSubjectHelper(const RDFSubjectHelper& orig);
    virtual ~RDFSubjectHelper();
    
    operator RDFSubject_t*();
    operator RDFSubject_t&();
    operator ANY_t*();
    RDFPredicateHelperPtr operator [](const std::string& predicate); 
    bool containsPredicate(const std::string& predicate);
    
    RDFSubjectHelper& setSubject(const std::string& subject);
    RDFSubjectHelper& addPredicate(RDFPredicateHelper& predicate);
    
    std::string getOntologyClass();
    std::string getSubject();
    std::vector<RDFPredicateHelperPtr> getPredicates();
    std::vector<std::string> listPredicates();
    
    
private:
    RDFSubject_t* rdfSubject;
    bool own;
    
};


}
}

#endif /* RDFMODELHELPER_HPP */

