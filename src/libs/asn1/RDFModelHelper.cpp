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
#include "keto/asn1/CloneHelper.hpp"
#include "keto/asn1/StringUtils.hpp"
#include "include/keto/asn1/StringUtils.hpp"


namespace keto {
namespace asn1 {

RDFModelHelper::RDFModelHelper() {
    this->rdfModel = (RDFModel_t*)calloc(1, sizeof *rdfModel);
    this->rdfModel->action = RDFChange_persist;
}

RDFModelHelper::RDFModelHelper(const RDFChange_t& change) {
    this->rdfModel = (RDFModel_t*)calloc(1, sizeof *rdfModel);
    this->rdfModel->action = change;
}

RDFModelHelper::RDFModelHelper(RDFModel_t* rdfModel) : rdfModel(rdfModel) {
    
}
    
RDFModelHelper::RDFModelHelper(const RDFModelHelper& orig) {
    this->rdfModel = keto::asn1::clone<RDFModel>(orig.rdfModel,
            &asn_DEF_RDFModel);
}
    

RDFModelHelper::~RDFModelHelper() {
    if (this->rdfModel) {
        ASN_STRUCT_FREE(asn_DEF_RDFModel, this->rdfModel);
    }
}

RDFModelHelper& RDFModelHelper::setChange(const RDFChange_t& change) {
    this->rdfModel->action = change;
    return (*this);
}


RDFModelHelper& RDFModelHelper::addSubject(RDFSubjectHelper& rdfSubject) {
    RDFDataFormat_t* dataFormat = (RDFDataFormat_t*)calloc(1, sizeof *dataFormat);
    dataFormat->present = RDFDataFormat_PR_rdfSubject;
    RDFSubject_t* subject = rdfSubject.operator RDFSubject_t*();
    dataFormat->choice.rdfSubject = *subject;
    if (0!= ASN_SEQUENCE_ADD(&this->rdfModel->rdfDataFormat,dataFormat)) {
        BOOST_THROW_EXCEPTION(keto::asn1::FailedToAddSubjectToModelException());
    }
    return (*this);
}

std::vector<std::string> RDFModelHelper::subjects() {
    std::vector<std::string> result;
    for (int index = 0; index < this->rdfModel->rdfDataFormat.list.count; index++) {
        if (this->rdfModel->rdfDataFormat.list.array[index]->present != RDFDataFormat_PR_rdfSubject) {
            continue;
        }
        
        result.push_back(StringUtils::copyBuffer(
                this->rdfModel->rdfDataFormat.list.array[index]->choice.rdfSubject.subject));
    }
    return result;
}

std::vector<RDFSubjectHelperPtr> RDFModelHelper::getSubjects() {
    std::vector<RDFSubjectHelperPtr> result;
    for (int index = 0; index < this->rdfModel->rdfDataFormat.list.count; index++) {
        result.push_back(RDFSubjectHelperPtr(new RDFSubjectHelper(
                &this->rdfModel->rdfDataFormat.list.array[index]->choice.rdfSubject,false)));
    }
    
    return result;
}

bool RDFModelHelper::contains(const std::string& subject) {
    for (int index = 0; index < this->rdfModel->rdfDataFormat.list.count; index++) {
        if (this->rdfModel->rdfDataFormat.list.array[index]->present != RDFDataFormat_PR_rdfSubject) {
            continue;
        }
        std::string subjectName = StringUtils::copyBuffer(
                this->rdfModel->rdfDataFormat.list.array[index]->choice.rdfSubject.subject);
        if (subjectName.compare(subject) != 0) {
            continue;
        }
        return true;
    }
    return false;
}

RDFSubjectHelperPtr RDFModelHelper::operator [](const std::string& subject) {
    std::cout << "Loop through entries : " << this->rdfModel->rdfDataFormat.list.count << std::endl;
    for (int index = 0; index < this->rdfModel->rdfDataFormat.list.count; index++) {
        if (this->rdfModel->rdfDataFormat.list.array[index]->present != RDFDataFormat_PR_rdfSubject) {
            continue;
        }
        
        std::string subjectName = StringUtils::copyBuffer(
                this->rdfModel->rdfDataFormat.list.array[index]->choice.rdfSubject.subject);
        std::cout << "Compare subjects [" << subjectName << "][" << subject << "]" << std::endl;
        if (subjectName.compare(subject) != 0) {
            continue;
        }
        std::cout << "Return the entries[" << subject << "]" << std::endl;
        
        return RDFSubjectHelperPtr(new RDFSubjectHelper(keto::asn1::clone<RDFSubject>(
                &this->rdfModel->rdfDataFormat.list.array[index]->choice.rdfSubject,
                &asn_DEF_RDFSubject)));
    }
    std::stringstream ss;
    ss << "The subject was not found [" << subject.size() << "][" << subject << "]";
    BOOST_THROW_EXCEPTION(keto::asn1::SubjectNotFoundInModelException(ss.str()));
}

RDFModelHelper::operator RDFModel_t&() {
    return *this->rdfModel;
}

RDFModelHelper::operator RDFModel_t*() {
    RDFModel_t* result = this->rdfModel;
    this->rdfModel = 0;
    return result;
}

RDFModelHelper::operator ANY_t*() {
    ANY_t* anyPtr = ANY_new_fromType(&asn_DEF_RDFModel, this->rdfModel);
    if (!anyPtr) {
        BOOST_THROW_EXCEPTION(keto::asn1::TypeToAnyConversionFailedException());
    }
    return anyPtr;
}


}
}
