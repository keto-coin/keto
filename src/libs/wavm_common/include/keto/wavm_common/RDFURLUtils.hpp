/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RDFURLUtils.hpp
 * Author: ubuntu
 *
 * Created on May 15, 2018, 10:58 AM
 */

#ifndef RDFURLUTILS_HPP
#define RDFURLUTILS_HPP

#include <string>

namespace keto {
namespace wavm_common {


class RDFURLUtils {
public:
    RDFURLUtils(const std::string& url);
    RDFURLUtils(const RDFURLUtils& orig) = default;
    virtual ~RDFURLUtils();
    
    std::string getModelName();
    std::string getModelBaseUrl();
    
    std::string buildSubjectUrl(const std::string& id);
    std::string buildPredicateUrl(const std::string& predicate);
    
private:
    std::string modelName;
    std::string modelBaseUrl;
};


}
}

#endif /* RDFURLUTILS_HPP */

