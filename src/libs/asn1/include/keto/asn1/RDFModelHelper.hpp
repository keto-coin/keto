/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RDFModelHelper.hpp
 * Author: ubuntu
 *
 * Created on March 12, 2018, 5:17 PM
 */

#ifndef RDFMODELHELPER_HPP
#define RDFMODELHELPER_HPP

#include <string>
#include <vector>
#include <memory>

#include "RDFChange.h"
#include "RDFModel.h"

#include "keto/asn1/RDFSubjectHelper.hpp"

namespace keto {
namespace asn1 {

class RDFModelHelper;
typedef std::shared_ptr<RDFModelHelper> RDFModelHelperPtr;
    
class RDFModelHelper {
public:
    RDFModelHelper();
    RDFModelHelper(const RDFChange_t& change);
    RDFModelHelper(RDFModel_t* rdfModel);
    RDFModelHelper(const RDFModelHelper& orig);
    virtual ~RDFModelHelper();
    
    RDFModelHelper& setChange(const RDFChange_t& change);
    RDFModelHelper& addSubject(RDFSubjectHelper& rdfSubject);
    
    std::vector<std::string> subjects();
    bool contains(const std::string& subject);
    RDFSubjectHelper operator [](const std::string& subject); 
    
    operator RDFModel_t&();
    operator RDFModel_t*();
    operator ANY_t*();
    
private:
    RDFModel_t* rdfModel;
};


}
}


#endif /* RDFMODELHELPER_HPP */

