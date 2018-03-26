/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RDFPredicateHelper.hpp
 * Author: ubuntu
 *
 * Created on March 11, 2018, 12:40 PM
 */

#ifndef RDFPREDICATEHELPER_HPP
#define RDFPREDICATEHELPER_HPP

#include <string>
#include <vector>
#include <memory>

#include "RDFPredicate.h"
#include "ANY.h"

#include "keto/asn1/RDFObjectHelper.hpp"

namespace keto {
namespace asn1 {

class RDFPredicateHelper;
typedef std::shared_ptr<RDFPredicateHelper> RDFPredicateHelperPtr;

class RDFPredicateHelper {
public:
    RDFPredicateHelper();
    RDFPredicateHelper(RDFPredicate_t* rdfPredicate);
    RDFPredicateHelper(RDFPredicate_t& rdfPredicate);
    RDFPredicateHelper(const std::string& predicate);
    RDFPredicateHelper(const RDFPredicateHelper& orig);
    virtual ~RDFPredicateHelper();
    
    operator RDFPredicate_t*();
    operator ANY_t*();
    
    RDFPredicateHelper& addObject(RDFObjectHelper& rdfObject);
    RDFPredicateHelper& setPredicate(const std::string& predicate);
    
    std::string getPredicate();
    std::vector<RDFObjectHelperPtr> listObjects();
    
private:
    RDFPredicate_t* rdfPredicate;
};

}
}

#endif /* RDFPREDICATEHELPER_HPP */

