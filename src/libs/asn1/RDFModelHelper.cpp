/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RDFModelHelper.cpp
 * Author: ubuntu
 * 
 * Created on March 12, 2018, 5:17 PM
 */

#include "RDFDataFormat.h"
#include "keto/asn1/RDFModelHelper.hpp"
#include "keto/asn1/RDFSubjectHelper.hpp"
#include "keto/asn1/Exception.hpp"

namespace keto {
namespace asn1 {

RDFModelHelper::RDFModelHelper() : change(RDFChange_persist) {
}

RDFModelHelper::RDFModelHelper(const RDFChange_t& change) : change(change) {
}
    

RDFModelHelper::~RDFModelHelper() {
}

RDFModelHelper& RDFModelHelper::setChange(const RDFChange_t& change) {
    this->change = change;
    return (*this);
}


RDFModelHelper& RDFModelHelper::addSubject(const RDFSubjectHelper& subject) {
    this->subjects.push_back(subject);
    return (*this);
}

RDFModelHelper::operator RDFModel_t*() {
    RDFModel_t* rdfModel = (RDFModel_t*)calloc(1, sizeof *rdfModel);
    rdfModel->action = change;
    
    for (RDFSubjectHelper rdfSubject : this->subjects) {
        RDFDataFormat_t* dataFormat = (RDFDataFormat_t*)calloc(1, sizeof *dataFormat);
        dataFormat->present = RDFDataFormat_PR_rdfSubject;
        RDFSubject_t* subject = rdfSubject.operator RDFSubject_t*();
        dataFormat->choice.rdfSubject = *subject;
        // free the subject memory, the rest is copied.
        free(subject);
        if (0!= ASN_SEQUENCE_ADD(&rdfModel->rdfDataFormat,dataFormat)) {
            BOOST_THROW_EXCEPTION(keto::asn1::FailedToAddSubjectToModelException());
        }
    }
    return rdfModel;
}

RDFModelHelper::operator ANY_t*() {
    RDFModel_t* ptr = this->operator RDFModel_t*();
    ANY_t* anyPtr = (ANY_t*)calloc(1, sizeof anyPtr);
    if (ANY_fromType(anyPtr, &asn_DEF_RDFModel, ptr) == -1) {
        free(anyPtr);
        BOOST_THROW_EXCEPTION(keto::asn1::TypeToAnyConversionFailedException());
    }
    return anyPtr;
}


}
}
