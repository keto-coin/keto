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
#include "keto/asn1/CloneHelper.hpp"

namespace keto {
namespace asn1 {

RDFPredicateHelper::RDFPredicateHelper() : own(true) {
    this->rdfPredicate = (RDFPredicate_t*)calloc(1, sizeof *rdfPredicate);
}

RDFPredicateHelper::RDFPredicateHelper(RDFPredicate_t* rdfPredicate) : 
    rdfPredicate(rdfPredicate), own(true) {
}

RDFPredicateHelper::RDFPredicateHelper(RDFPredicate_t* rdfPredicate, bool own) : 
    rdfPredicate(rdfPredicate), own(own) {
}


RDFPredicateHelper::RDFPredicateHelper(RDFPredicate_t& rdfPredicate) : own(true) {
    this->rdfPredicate = keto::asn1::clone<RDFPredicate_t>(&rdfPredicate,
            &asn_DEF_RDFPredicate);
}

RDFPredicateHelper::RDFPredicateHelper(const std::string& predicate) : own(true) {
    this->rdfPredicate = (RDFPredicate_t*)calloc(1, sizeof *rdfPredicate);
    OCTET_STRING_fromBuf(&rdfPredicate->predicate,
            predicate.c_str(),predicate.size());
}

RDFPredicateHelper::RDFPredicateHelper(const RDFPredicateHelper& orig) : own(true) {
    this->rdfPredicate = keto::asn1::clone<RDFPredicate_t>(orig.rdfPredicate,
            &asn_DEF_RDFPredicate);
}

RDFPredicateHelper::~RDFPredicateHelper() {
    if (this->rdfPredicate && own) {
        ASN_STRUCT_FREE(asn_DEF_RDFPredicate, this->rdfPredicate);
    }
}

RDFPredicateHelper::operator RDFPredicate_t*() {
    RDFPredicate_t* result = this->rdfPredicate;
    this->rdfPredicate = 0;
    return result;
}


RDFPredicateHelper::operator ANY_t*() {
    ANY_t* anyPtr = ANY_new_fromType(&asn_DEF_RDFPredicate, this->rdfPredicate);
    if (!anyPtr) {
        BOOST_THROW_EXCEPTION(keto::asn1::TypeToAnyConversionFailedException());
    }
    return anyPtr;
}


RDFPredicateHelper& RDFPredicateHelper::addObject(RDFObjectHelper& rdfObject) {
    if (0!= ASN_SEQUENCE_ADD(&rdfPredicate->rdfObjects,rdfObject.operator RDFObject_t*())) {
        BOOST_THROW_EXCEPTION(keto::asn1::FailedToAddObjectToPredicateException());
    }
    return (*this);
}


RDFPredicateHelper& RDFPredicateHelper::setPredicate(const std::string& predicate) {
    OCTET_STRING_fromBuf(&rdfPredicate->predicate,
            predicate.c_str(),predicate.size());
    return (*this);
}

std::string RDFPredicateHelper::getPredicate() {
    return std::string((const char*)this->rdfPredicate->predicate.buf);
}

std::vector<RDFObjectHelperPtr> RDFPredicateHelper::listObjects() {
    std::vector<RDFObjectHelperPtr> result;
    for (int index = 0; index < this->rdfPredicate->rdfObjects.list.count; index++) {
        result.push_back(RDFObjectHelperPtr(
                new RDFObjectHelper(*this->rdfPredicate->rdfObjects.list.array[index])));
    }
    return result;
}


}
}
