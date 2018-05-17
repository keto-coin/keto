/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RDFMemorySession.cpp
 * Author: ubuntu
 * 
 * Created on May 10, 2018, 6:40 AM
 */

#include <cstdlib>

#include "keto/wavm_common/RDFMemorySession.hpp"

#include "keto/wavm_common/Exception.hpp"
#include "keto/wavm_common/RDFConstants.hpp"
#include "keto/asn1/Constants.hpp"

namespace keto {
namespace wavm_common {

RDFMemorySession::RDFMemorySession() {
    this->world = librdf_new_world();
    librdf_world_open(this->world);
    storage=librdf_new_storage(this->world, "memory", NULL, NULL);
    model = librdf_new_model(world,storage,NULL);
}

RDFMemorySession::~RDFMemorySession() {
    librdf_free_model(model);
    librdf_free_storage(storage);
    librdf_free_world(world);
}

void RDFMemorySession::persist(keto::asn1::RDFSubjectHelperPtr& subject) {
    // add the subject to the in memory store
    for (keto::asn1::RDFPredicateHelperPtr predicateHelper : subject->getPredicates()) {
        for (keto::asn1::RDFObjectHelperPtr objectHelper : predicateHelper->listObjects()) {
            librdf_statement* statement= 0;
            if (objectHelper->getType().compare(keto::asn1::Constants::RDF_NODE::LITERAL) == 0) {
                statement = librdf_new_statement_from_nodes(this->world, 
                    librdf_new_node_from_uri_string(this->world, (const unsigned char*)subject->getSubject().c_str()),
                    librdf_new_node_from_uri_string(this->world, (const unsigned char*)predicateHelper->getPredicate().c_str()),
                    librdf_new_node_from_typed_literal(
                            this->world, 
                            (const unsigned char*)objectHelper->getValue().c_str(),
                            NULL, 
                            librdf_new_uri(
                                this->world,
                                (const unsigned char*)objectHelper->getDataType().c_str()))
                    );
            } else if (objectHelper->getType().compare(keto::asn1::Constants::RDF_NODE::URI) == 0) {
                    statement= librdf_new_statement_from_nodes(this->world, 
                        librdf_new_node_from_uri_string(this->world, (const unsigned char*)subject->getSubject().c_str()),
                        librdf_new_node_from_uri_string(this->world, (const unsigned char*)predicateHelper->getPredicate().c_str()),
                        librdf_new_node_from_uri_string(this->world, (const unsigned char*)objectHelper->getValue().c_str())
                        );
            } else {
                std::stringstream ss;
                ss << "The rdf format [" << objectHelper->getType() << "] is currently not supported";
                BOOST_THROW_EXCEPTION(keto::wavm_common::UnsupportedDataTypeTransactionException(
                        ss.str()));
            }
            librdf_model_add_statement(this->model, statement);

             /* Free what we just used to add to the model - now it should be stored */
            librdf_free_statement(statement);
        }
    }
}

ResultVectorMap RDFMemorySession::executeQuery(const std::string& queryStr) {
    librdf_query* query;
    librdf_query_results* results;
    query = librdf_new_query(this->world, "sparql", 
            NULL, (const unsigned char *)queryStr.c_str(), NULL);
    results = librdf_model_query_execute(this->model, query);
    ResultVectorMap resultVectorMap;
    if (!results) {
        librdf_free_query(query);
        return resultVectorMap;
    }
    const char **names=NULL;
    
    if(!librdf_query_results_get_bindings(results, &names, NULL)) {
        int bindingCount = librdf_query_results_get_bindings_count(results);
        while (!librdf_query_results_finished(results)) {
            ResultMap resultMap;
            for (int index = 0; index < bindingCount; index++) {
                librdf_node* node = librdf_query_results_get_binding_value_by_name(results,
                        names[index]);
                unsigned char* value = librdf_node_get_literal_value(node);
                resultMap[names[index]] = std::string((const char*)value);
                librdf_free_node(node);
            }
            resultVectorMap.push_back(resultMap);
            librdf_query_results_next(results);
        }
    }
    librdf_free_query_results(results);
    librdf_free_query(query);
    
    return resultVectorMap;
}


std::string RDFMemorySession::getStringValue(
        const std::string& subject, const std::string& predicate) {
    librdf_iterator* rdfIter =
        librdf_model_get_targets(
            this->model,
            librdf_new_node_from_uri_string(this->world, (const unsigned char*)subject.c_str()),
            librdf_new_node_from_uri_string(this->world, (const unsigned char*)predicate.c_str()));
    
    if (librdf_iterator_end(rdfIter)) {
        librdf_free_iterator(rdfIter);
        std::stringstream ss;
        ss << "The rdf node [" << subject << "][" << predicate << "] was not found";
        BOOST_THROW_EXCEPTION(keto::wavm_common::UnsupportedDataTypeTransactionException(
                ss.str()));
    }
    librdf_node* target=(librdf_node*)librdf_iterator_get_object(rdfIter);
    unsigned char* value = librdf_node_get_literal_value(target);
    std::string result((const char*)value);
    librdf_free_iterator(rdfIter);
    return result;
}

long RDFMemorySession::getLongValue(const std::string& subject,
        const std::string& predicate) {
    librdf_iterator* rdfIter =
        librdf_model_get_targets(
            this->model,
            librdf_new_node_from_uri_string(this->world, (const unsigned char*)subject.c_str()),
            librdf_new_node_from_uri_string(this->world, (const unsigned char*)predicate.c_str()));
    
    if (librdf_iterator_end(rdfIter)) {
        librdf_free_iterator(rdfIter);
        std::stringstream ss;
        ss << "The rdf node [" << subject << "][" << predicate << "] was not found";
        BOOST_THROW_EXCEPTION(keto::wavm_common::UnsupportedDataTypeTransactionException(
                ss.str()));
    }
    librdf_node* target=(librdf_node*)librdf_iterator_get_object(rdfIter);
    unsigned char* value = librdf_node_get_literal_value(target);
    long result = atol((const char*)value);
    librdf_free_iterator(rdfIter);
    return result;
}

float RDFMemorySession::getFloatValue(const std::string& subject,
        const std::string& predicate) {
    librdf_iterator* rdfIter =
        librdf_model_get_targets(
            this->model,
            librdf_new_node_from_uri_string(this->world, (const unsigned char*)subject.c_str()),
            librdf_new_node_from_uri_string(this->world, (const unsigned char*)predicate.c_str()));
    
    if (librdf_iterator_end(rdfIter)) {
        librdf_free_iterator(rdfIter);
        std::stringstream ss;
        ss << "The rdf node [" << subject << "][" << predicate << "] was not found";
        BOOST_THROW_EXCEPTION(keto::wavm_common::UnsupportedDataTypeTransactionException(
                ss.str()));
    }
    librdf_node* target=(librdf_node*)librdf_iterator_get_object(rdfIter);
    unsigned char* value = librdf_node_get_literal_value(target);
    float result = atof((const char*)value);
    librdf_free_iterator(rdfIter);
    return result;
}

bool RDFMemorySession::getBooleanValue(const std::string& subject,
        const std::string& predicate) {
    librdf_iterator* rdfIter =
        librdf_model_get_targets(
            this->model,
            librdf_new_node_from_uri_string(this->world, (const unsigned char*)subject.c_str()),
            librdf_new_node_from_uri_string(this->world, (const unsigned char*)predicate.c_str()));
    
    if (librdf_iterator_end(rdfIter)) {
        librdf_free_iterator(rdfIter);
        std::stringstream ss;
        ss << "The rdf node [" << subject << "][" << predicate << "] was not found";
        BOOST_THROW_EXCEPTION(keto::wavm_common::UnsupportedDataTypeTransactionException(
                ss.str()));
    }
    librdf_node* target=(librdf_node*)librdf_iterator_get_object(rdfIter);
    unsigned char* value = librdf_node_get_literal_value(target);
    std::string result((const char*)value);
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    bool resultBool = false;
    if (result.compare("true")) {
        resultBool = true;
    }
    librdf_free_iterator(rdfIter);
    return resultBool;
}

time_t RDFMemorySession::getDateTimeValue(const std::string& subject, const std::string& predicate) {
    librdf_iterator* rdfIter =
        librdf_model_get_targets(
            this->model,
            librdf_new_node_from_uri_string(this->world, (const unsigned char*)subject.c_str()),
            librdf_new_node_from_uri_string(this->world, (const unsigned char*)predicate.c_str()));
    
    if (librdf_iterator_end(rdfIter)) {
        librdf_free_iterator(rdfIter);
        std::stringstream ss;
        ss << "The rdf node [" << subject << "][" << predicate << "] was not found";
        BOOST_THROW_EXCEPTION(keto::wavm_common::UnsupportedDataTypeTransactionException(
                ss.str()));
    }
    librdf_node* target=(librdf_node*)librdf_iterator_get_object(rdfIter);
    unsigned char* value = librdf_node_get_literal_value(target);
    std::string timeString((const char*)value);
    struct tm tm;
    strptime(timeString.c_str(), "%Y-%m-%dT%X", &tm);
    time_t result = mktime(&tm);
    librdf_free_iterator(rdfIter);
    return result;
}

// set method
void RDFMemorySession::setStringValue(const std::string& subject, const std::string& predicate,
        const std::string& value) {
    librdf_statement* statement = librdf_new_statement_from_nodes(this->world, 
                        librdf_new_node_from_uri_string(this->world, (const unsigned char*)subject.c_str()),
                        librdf_new_node_from_uri_string(this->world, (const unsigned char*)predicate.c_str()),
                        librdf_new_node_from_typed_literal(
                            this->world, 
                            (const unsigned char*)value.c_str(),
                            NULL, 
                            librdf_new_uri(
                                this->world,
                                (const unsigned char *)RDFConstants::TYPES::STRING))
                        );
    librdf_model_add_statement(this->model, statement);
    librdf_free_statement(statement);
}

void RDFMemorySession::setLongValue(const std::string& subject, const std::string& predicate,
        const long value) {
    std::stringstream ss;
    ss << value;
    librdf_statement* statement = librdf_new_statement_from_nodes(this->world, 
                        librdf_new_node_from_uri_string(this->world, (const unsigned char*)subject.c_str()),
                        librdf_new_node_from_uri_string(this->world, (const unsigned char*)predicate.c_str()),
                        librdf_new_node_from_typed_literal(
                            this->world, 
                            (const unsigned char*)ss.str().c_str(),
                            NULL, 
                            librdf_new_uri(
                                this->world,
                                (const unsigned char *)RDFConstants::TYPES::LONG))
                        );
    librdf_model_add_statement(this->model, statement);
    librdf_free_statement(statement);
}

void RDFMemorySession::setFloatValue(const std::string& subject, const std::string& predicate,
        const float value) {
    std::stringstream ss;
    ss << value;
    librdf_statement* statement = librdf_new_statement_from_nodes(this->world, 
                        librdf_new_node_from_uri_string(this->world, (const unsigned char*)subject.c_str()),
                        librdf_new_node_from_uri_string(this->world, (const unsigned char*)predicate.c_str()),
                        librdf_new_node_from_typed_literal(
                            this->world, 
                            (const unsigned char*)ss.str().c_str(),
                            NULL, 
                            librdf_new_uri(
                                this->world,
                                (const unsigned char *)RDFConstants::TYPES::FLOAT))
                        );
    librdf_model_add_statement(this->model, statement);
    librdf_free_statement(statement);
}

void RDFMemorySession::setBooleanValue(const std::string& subject, const std::string& predicate,
        const bool value) {
    std::stringstream ss;
    if (value) {
        ss << "true";
    } else {
        ss << "false";
    }
    librdf_statement* statement = librdf_new_statement_from_nodes(this->world, 
                        librdf_new_node_from_uri_string(this->world, (const unsigned char*)subject.c_str()),
                        librdf_new_node_from_uri_string(this->world, (const unsigned char*)predicate.c_str()),
                        librdf_new_node_from_typed_literal(
                            this->world, 
                            (const unsigned char*)ss.str().c_str(),
                            NULL, 
                            librdf_new_uri(
                                this->world,
                                (const unsigned char *)RDFConstants::TYPES::BOOLEAN))
                        );
    librdf_model_add_statement(this->model, statement);
    librdf_free_statement(statement);
}


void RDFMemorySession::setDateTimeValue(const std::string& subject, const std::string& predicate,
            const time_t value) {
    std::stringstream ss;
    struct tm  tstruct;
    char       buf[80];
    struct tm result;
    localtime_r(&value,&result);
    strftime(buf, sizeof(buf), "%Y-%m-%dT%X", &tstruct);
    
    librdf_statement* statement = librdf_new_statement_from_nodes(this->world, 
                        librdf_new_node_from_uri_string(this->world, (const unsigned char*)subject.c_str()),
                        librdf_new_node_from_uri_string(this->world, (const unsigned char*)predicate.c_str()),
                        librdf_new_node_from_typed_literal(
                            this->world, 
                            (const unsigned char*)buf,
                            NULL, 
                            librdf_new_uri(
                                this->world,
                                (const unsigned char *)RDFConstants::TYPES::DATE_TIME))
                        );
    librdf_model_add_statement(this->model, statement);
    librdf_free_statement(statement);
}

}
}
