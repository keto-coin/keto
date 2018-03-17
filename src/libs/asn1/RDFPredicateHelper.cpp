/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RDFPredicateHelper.cpp
 * Author: ubuntu
 * 
 * Created on March 11, 2018, 12:40 PM
 */

#include "keto/asn1/RDFPredicateHelper.hpp"
#include "keto/asn1/Exception.hpp"
#include "keto/asn1/RDFObjectHelper.hpp"

namespace keto {
namespace asn1 {

RDFPredicateHelper::RDFPredicateHelper() {
}

RDFPredicateHelper::RDFPredicateHelper(const std::string& predicate) : 
    predicate(predicate) {
}
    

RDFPredicateHelper::~RDFPredicateHelper() {
}

RDFPredicateHelper::operator RDFPredicate_t*() {
    RDFPredicate_t* rdfPredicate = (RDFPredicate_t*)calloc(1, sizeof *rdfPredicate);
    OCTET_STRING_fromBuf(&rdfPredicate->predicate,
            this->predicate.c_str(),this->predicate.size());
    
    for (RDFObjectHelper rdfObject : this->objects) {
        if (0!= ASN_SEQUENCE_ADD(&rdfPredicate->rdfObjects,rdfObject.operator RDFObject_t*())) {
            BOOST_THROW_EXCEPTION(keto::asn1::FailedToAddObjectToPredicateException());
        }
    }
    return rdfPredicate;
}

RDFPredicateHelper::operator ANY_t*() {
    RDFPredicate_t* ptr = this->operator RDFPredicate_t*();
    ANY_t* anyPtr = ANY_new_fromType(&asn_DEF_RDFPredicate, ptr);
    ASN_STRUCT_FREE(asn_DEF_RDFPredicate, ptr);
    if (!anyPtr) {
        BOOST_THROW_EXCEPTION(keto::asn1::TypeToAnyConversionFailedException());
    }
    
    return anyPtr;
}

RDFPredicateHelper& RDFPredicateHelper::addObject(const RDFObjectHelper& rdfObject) {
    this->objects.push_back(rdfObject);
    return (*this);
}


RDFPredicateHelper& RDFPredicateHelper::setPredicate(const std::string& predicate) {
    this->predicate = predicate;
    return (*this);
}
    

}
}
