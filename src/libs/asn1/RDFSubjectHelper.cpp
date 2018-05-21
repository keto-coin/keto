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
#include "keto/asn1/Exception.hpp"
#include "keto/asn1/CloneHelper.hpp"
#include "keto/asn1/StringUtils.hpp"


namespace keto {
namespace asn1 {

RDFSubjectHelper::RDFSubjectHelper() : own(true) {
    rdfSubject = (RDFSubject_t*)calloc(1, sizeof *rdfSubject);
}

RDFSubjectHelper::RDFSubjectHelper(RDFSubject_t* rdfSubject) :
    rdfSubject(rdfSubject), own(true) {
}

RDFSubjectHelper::RDFSubjectHelper(RDFSubject_t* rdfSubject, bool own) :
    rdfSubject(rdfSubject), own(own) {
    
}

RDFSubjectHelper::RDFSubjectHelper(const std::string& subject) : own(true) {
    rdfSubject = (RDFSubject_t*)calloc(1, sizeof *rdfSubject);
    OCTET_STRING_fromBuf(&rdfSubject->subject,
            subject.c_str(),subject.size());
}


RDFSubjectHelper::RDFSubjectHelper(const RDFSubjectHelper& orig) {
    // clone the rdf subject
    this->rdfSubject = keto::asn1::clone<RDFSubject>(orig.rdfSubject,
            &asn_DEF_RDFSubject);
}

RDFSubjectHelper::~RDFSubjectHelper() {
    if (own && this->rdfSubject) {
        ASN_STRUCT_FREE(asn_DEF_RDFSubject, this->rdfSubject);
    }
}


RDFSubjectHelper::operator RDFSubject_t*() {
    RDFSubject_t* result = this->rdfSubject;
    this->rdfSubject = 0;
    return result;
}

RDFSubjectHelper::operator RDFSubject_t&() {
    return *this->rdfSubject;
}

RDFSubjectHelper::operator ANY_t*() {
    ANY_t* anyPtr = ANY_new_fromType(&asn_DEF_RDFSubject, this->rdfSubject);
    if (!anyPtr) {
        BOOST_THROW_EXCEPTION(keto::asn1::TypeToAnyConversionFailedException());
    }
    return anyPtr;
}

bool RDFSubjectHelper::containsPredicate(const std::string& predicate) {
    for (int index = 0; index < this->rdfSubject->rdfPredicates.list.count; index++) {
        std::string name = 
                StringUtils::copyBuffer(this->rdfSubject->rdfPredicates.list.array[index]->predicate);
        if (name.compare(predicate) == 0) {
            return true;
        }
    }
    return false;
}

RDFPredicateHelperPtr RDFSubjectHelper::operator [](const std::string& predicate) {
    for (int index = 0; index < this->rdfSubject->rdfPredicates.list.count; index++) {
        std::string name = StringUtils::copyBuffer(
                this->rdfSubject->rdfPredicates.list.array[index]->predicate);
        if (name.compare(predicate) == 0) {
            return RDFPredicateHelperPtr(new RDFPredicateHelper(
                        this->rdfSubject->rdfPredicates.list.array[index],false));
        }
    }
    BOOST_THROW_EXCEPTION(keto::asn1::PredicateNotFoundException());
}

RDFSubjectHelper& RDFSubjectHelper::setSubject(const std::string& subject) {
    OCTET_STRING_fromBuf(&rdfSubject->subject,
            subject.c_str(),subject.size());
    return (*this);
}

RDFSubjectHelper& RDFSubjectHelper::addPredicate(RDFPredicateHelper& predicate) {
    if (0!= ASN_SEQUENCE_ADD(&rdfSubject->rdfPredicates,predicate.operator RDFPredicate_t*())) {
        BOOST_THROW_EXCEPTION(keto::asn1::FailedToAddPredicateToSubjectException());
    }
    return (*this);
}

std::string RDFSubjectHelper::getOntologyClass() {
    std::string subject = getSubject();
    return subject.substr(0,subject.find_last_of("/"));
}

std::string RDFSubjectHelper::getSubject() {
    return StringUtils::copyBuffer(this->rdfSubject->subject);
}

std::vector<RDFPredicateHelperPtr> RDFSubjectHelper::getPredicates() {
    std::vector<RDFPredicateHelperPtr> result;
    for (int index = 0; index < this->rdfSubject->rdfPredicates.list.count; index++) {
        result.push_back(RDFPredicateHelperPtr(new RDFPredicateHelper(
                    this->rdfSubject->rdfPredicates.list.array[index],false)));
    }
    return result;
}

std::vector<std::string> RDFSubjectHelper::listPredicates() {
    std::vector<std::string> result;
    for (int index = 0; index < this->rdfSubject->rdfPredicates.list.count; index++) {
        result.push_back(StringUtils::copyBuffer(
                this->rdfSubject->rdfPredicates.list.array[index]->predicate));
    }
    return result;
}
    

}
}
