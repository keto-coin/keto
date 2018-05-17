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
#include <ctime>

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
    
    // get methods
    std::string getStringValue(const std::string& subject, const std::string& predicate);
    long getLongValue(const std::string& subject, const std::string& predicate);
    float getFloatValue(const std::string& subject, const std::string& predicate);
    bool getBooleanValue(const std::string& subject, const std::string& predicate);
    time_t getDateTimeValue(const std::string& subject, const std::string& predicate);
    
    // set method
    void setStringValue(const std::string& subject, const std::string& predicate,
            const std::string& value);
    void setLongValue(const std::string& subject, const std::string& predicate,
            const long value);
    void setFloatValue(const std::string& subject, const std::string& predicate,
            const float value);
    void setBooleanValue(const std::string& subject, const std::string& predicate,
            const bool value);
    void setDateTimeValue(const std::string& subject, const std::string& predicate,
            const time_t value);
    
    
private:
    librdf_world* world;
    librdf_storage* storage;
    librdf_model* model;
};


}
}

#endif /* RDFMEMORYSESSION_HPP */

