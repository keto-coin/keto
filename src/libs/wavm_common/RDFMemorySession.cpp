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

#include "keto/wavm_common/RDFMemorySession.hpp"

#include "keto/wavm_common/Exception.hpp"
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

        
}
}
