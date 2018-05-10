/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RDFMemorySession.hpp
 * Author: ubuntu
 *
 * Created on May 10, 2018, 6:40 AM
 */

#ifndef RDFMEMORYSESSION_HPP
#define RDFMEMORYSESSION_HPP

#include <string>
#include <memory>
#include <vector>
#include <map>

#include <librdf.h>
#include <redland.h>
#include <rdf_storage.h>
#include <rdf_model.h>

#include "keto/asn1/RDFSubjectHelper.hpp"

namespace keto {
namespace wavm_common {

class RDFMemorySession;
typedef std::shared_ptr<RDFMemorySession> RDFMemorySessionPtr;
typedef std::map<std::string,std::string> ResultMap;
typedef std::vector<ResultMap> ResultVectorMap;


class RDFMemorySession {
public:
    RDFMemorySession();
    RDFMemorySession(const RDFMemorySession& orig) = delete;
    virtual ~RDFMemorySession();
    
    void persist(keto::asn1::RDFSubjectHelperPtr& subject);
    ResultVectorMap executeQuery(const std::string& queryStr);
    
private:
    librdf_world* world;
    librdf_storage* storage;
    librdf_model* model;
};


}
}

#endif /* RDFMEMORYSESSION_HPP */

