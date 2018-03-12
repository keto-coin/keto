/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RDFModelHelper.cpp
 * Author: ubuntu
 * 
 * Created on March 11, 2018, 12:24 PM
 */

#include "keto/asn1/RDFSubjectHelper.hpp"
#include "keto/asn1/RDFSubjectHelper.hpp"
#include "keto/asn1/Exception.hpp"
#include "include/keto/asn1/RDFSubjectHelper.hpp"


namespace keto {
namespace asn1 {

RDFSubjectHelper::RDFSubjectHelper() {
}

RDFSubjectHelper::RDFSubjectHelper(const std::string& subject) : 
    subject(subject) {
}

RDFSubjectHelper::~RDFSubjectHelper() {
    
}

RDFSubjectHelper::operator RDFSubject_t*() {
    RDFSubject_t* rdfSubject = (RDFSubject_t*)calloc(1, sizeof *rdfSubject);
    OCTET_STRING_fromBuf(&rdfSubject->subject,
            this->subject.c_str(),this->subject.size());
    for (RDFPredicateHelper rdfPredicate : this->predicates) {
        if (0!= ASN_SEQUENCE_ADD(&rdfSubject->rdfPredicates,rdfPredicate.operator RDFPredicate_t*())) {
            BOOST_THROW_EXCEPTION(keto::asn1::FailedToAddPredicateToSubjectException());
        }
    }
    return rdfSubject;
}

RDFSubjectHelper::operator ANY_t*() {
    RDFSubject_t* ptr = this->operator RDFSubject_t*();
    ANY_t* anyPtr = (ANY_t*)calloc(1, sizeof anyPtr);
    if (ANY_fromType(anyPtr, &asn_DEF_RDFSubject, ptr) == -1) {
        free(anyPtr);
        BOOST_THROW_EXCEPTION(keto::asn1::TypeToAnyConversionFailedException());
    }
    return anyPtr;
}

RDFSubjectHelper& RDFSubjectHelper::setSubject(const std::string& subject) {
    this->subject = subject;
    return (*this);
}

RDFSubjectHelper& RDFSubjectHelper::addPredicate(const RDFPredicateHelper& predicate) {
    this->predicates.push_back(predicate);
    return (*this);
}
    

}
}
