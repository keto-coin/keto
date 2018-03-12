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

#include "RDFPredicate.h"
#include "ANY.h"

#include "keto/asn1/RDFObjectHelper.hpp"

namespace keto {
namespace asn1 {


class RDFPredicateHelper {
public:
    RDFPredicateHelper();
    RDFPredicateHelper(const std::string& predicate);
    RDFPredicateHelper(const RDFPredicateHelper& orig) = default;
    virtual ~RDFPredicateHelper();
    
    operator RDFPredicate_t*();
    operator ANY_t*();
    
    RDFPredicateHelper& addObject(const RDFObjectHelper& rdfObject);
    RDFPredicateHelper& setPredicate(const std::string& predicate);
    
private:
    std::string predicate;
    std::vector<RDFObjectHelper> objects;
};

}
}

#endif /* RDFPREDICATEHELPER_HPP */

