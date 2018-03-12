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

#include "RDFChange.h"
#include "RDFModel.h"

#include "keto/asn1/RDFSubjectHelper.hpp"

namespace keto {
namespace asn1 {

class RDFModelHelper {
public:
    RDFModelHelper();
    RDFModelHelper(const RDFChange_t& change);
    RDFModelHelper(const RDFModelHelper& orig) = default;
    virtual ~RDFModelHelper();
    
    RDFModelHelper& setChange(const RDFChange_t& change);
    RDFModelHelper& addSubject(const RDFSubjectHelper& subject);
    
    operator RDFModel_t*();
    operator ANY_t*();
    
private:
    RDFChange_t change;
    std::vector<RDFSubjectHelper> subjects;
};


}
}


#endif /* RDFMODELHELPER_HPP */

