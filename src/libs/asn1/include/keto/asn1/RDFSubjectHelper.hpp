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

#include "RDFSubject.h"
#include "ANY.h"

#include "keto/asn1/RDFPredicateHelper.hpp"

namespace keto {
namespace asn1 {


class RDFSubjectHelper {
public:
    RDFSubjectHelper();
    RDFSubjectHelper(const std::string& subject);
    RDFSubjectHelper(const RDFSubjectHelper& orig) = default;
    virtual ~RDFSubjectHelper();
    
    operator RDFSubject_t*();
    operator ANY_t*();
    
    RDFSubjectHelper& setSubject(const std::string& subject);
    RDFSubjectHelper& addPredicate(const RDFPredicateHelper& predicate);
    
private:
    std::string subject;
    std::vector<RDFPredicateHelper> predicates;
    
    
};


}
}

#endif /* RDFMODELHELPER_HPP */

