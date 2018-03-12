/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RDFObjectHelper.cpp
 * Author: ubuntu
 * 
 * Created on March 11, 2018, 12:45 PM
 */

#include "keto/asn1/RDFObjectHelper.hpp"
#include "keto/asn1/Constants.hpp"
#include "keto/asn1/Exception.hpp"

namespace keto {
namespace asn1 {


RDFObjectHelper::RDFObjectHelper() : 
    type(Constants::RDF_TYPE), lang(Constants::RDF_LANGUAGE)
{
}

RDFObjectHelper::RDFObjectHelper(const std::string& value, const std::string& dataType) :
    value(value),type(Constants::RDF_TYPE), lang(Constants::RDF_LANGUAGE), dataType(dataType) {
}
    

RDFObjectHelper::~RDFObjectHelper() {
}

RDFObjectHelper::operator RDFObject_t*() {
    RDFObject_t* rdfObject = (RDFObject_t*)calloc(1, sizeof *rdfObject);
    
    
    OCTET_STRING_fromBuf(&rdfObject->value,
            this->value.c_str(),this->value.size());
    OCTET_STRING_fromBuf(&rdfObject->type,
            this->type.c_str(),this->type.size());
    OCTET_STRING_fromBuf(&rdfObject->lang,
            this->lang.c_str(),this->lang.size());
    OCTET_STRING_fromBuf(&rdfObject->dataType,
            this->dataType.c_str(),this->dataType.size());
    return rdfObject;
}


RDFObjectHelper::operator ANY_t*() {
    RDFObject_t* ptr = this->operator RDFObject_t*();
    ANY_t* anyPtr = (ANY_t*)calloc(1, sizeof anyPtr);
    if (ANY_fromType(anyPtr, &asn_DEF_RDFObject, ptr) == -1) {
        free(anyPtr);
        BOOST_THROW_EXCEPTION(keto::asn1::TypeToAnyConversionFailedException());
    }
    
    return anyPtr;
}


RDFObjectHelper& RDFObjectHelper::setValue(const std::string& value) {
    this->value = value;
    return (*this);
}


RDFObjectHelper& RDFObjectHelper::setType(const std::string& type) {
    this->type = type;
    return (*this);
}


RDFObjectHelper& RDFObjectHelper::setLang(const std::string& lang) {
    this->lang = lang;
    return (*this);
}


RDFObjectHelper& RDFObjectHelper::setDataType(const std::string& dataType) {
    this->dataType = dataType;
    return (*this);
}


}
}