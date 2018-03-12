/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RDFObjectHelpler.hpp
 * Author: ubuntu
 *
 * Created on March 11, 2018, 12:45 PM
 */

#ifndef RDFOBJECTHELPLER_HPP
#define RDFOBJECTHELPLER_HPP

#include <string>

#include "RDFObject.h"
#include "UTF8String.h"
#include "ANY.h"

namespace keto {
namespace asn1 {


class RDFObjectHelper {
public:
    RDFObjectHelper();
    RDFObjectHelper(const std::string& value, const std::string& dataType);
    RDFObjectHelper(const RDFObjectHelper& orig) = default;
    virtual ~RDFObjectHelper();
    
    operator RDFObject_t*();
    operator ANY_t*();
    
    
    RDFObjectHelper& setValue(const std::string& value);
    RDFObjectHelper& setType(const std::string& type);
    RDFObjectHelper& setLang(const std::string& lang);
    RDFObjectHelper& setDataType(const std::string& dataType);
    
    
private:
    std::string value;
    std::string type;
    std::string lang;
    std::string dataType;
    
};

}
}

#endif /* RDFOBJECTHELPLER_HPP */

