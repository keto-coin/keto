/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AccountGraphSession.cpp
 * Author: ubuntu
 * 
 * Created on March 28, 2018, 6:00 AM
 */

#include <iostream>
#include <sstream>

#include "keto/asn1/Constants.hpp"
#include "keto/account_db/AccountGraphSession.hpp"
#include "keto/account_db/Exception.hpp"
#include "include/keto/account_db/AccountGraphStore.hpp"
#include "include/keto/account_db/AccountGraphSession.hpp"
#include "keto/common/Log.hpp"

namespace keto {
namespace account_db {

    
// TODO: Implement a custom Berkely DB loader to support full transactions
// at present transaction rollback is not supported.

AccountGraphSession::~AccountGraphSession() {
    if (activeTransaction) {
        // rollback if active still at this point
        this->rollback();
    }
}

void AccountGraphSession::persist(keto::asn1::RDFSubjectHelperPtr& subject) {
    for (keto::asn1::RDFPredicateHelperPtr predicateHelper : subject->getPredicates()) {
        for (keto::asn1::RDFObjectHelperPtr objectHelper : predicateHelper->listObjects()) {
            librdf_statement* statement= 0;
            if (objectHelper->getType().compare(keto::asn1::Constants::RDF_NODE::LITERAL) == 0) {
                statement = librdf_new_statement_from_nodes(this->accountGraphStore->getWorld(), 
                    librdf_new_node_from_uri_string(this->accountGraphStore->getWorld(), (const unsigned char*)subject->getSubject().c_str()),
                    librdf_new_node_from_uri_string(this->accountGraphStore->getWorld(), (const unsigned char*)predicateHelper->getPredicate().c_str()),
                    librdf_new_node_from_typed_literal(
                            this->accountGraphStore->getWorld(), 
                            (const unsigned char*)objectHelper->getValue().c_str(),
                            NULL, 
                            librdf_new_uri(
                                this->accountGraphStore->getWorld(),
                                (const unsigned char*)objectHelper->getDataType().c_str()))
                    );
            } else if (objectHelper->getType().compare(keto::asn1::Constants::RDF_NODE::URI) == 0) {
                    statement= librdf_new_statement_from_nodes(this->accountGraphStore->getWorld(), 
                        librdf_new_node_from_uri_string(this->accountGraphStore->getWorld(), (const unsigned char*)subject->getSubject().c_str()),
                        librdf_new_node_from_uri_string(this->accountGraphStore->getWorld(), (const unsigned char*)predicateHelper->getPredicate().c_str()),
                        librdf_new_node_from_uri_string(this->accountGraphStore->getWorld(), (const unsigned char*)objectHelper->getValue().c_str())
                        );
            } else {
                std::stringstream ss;
                ss << "The rdf format [" << objectHelper->getType() << "] is currently not supported";
                BOOST_THROW_EXCEPTION(keto::account_db::UnsupportedDataTypeTransactionException(
                        ss.str()));
            }
            librdf_model_add_statement(this->accountGraphStore->getModel(), statement);

             /* Free what we just used to add to the model - now it should be stored */
            librdf_free_statement(statement);
        }
    }
}
    
void AccountGraphSession::remove(keto::asn1::RDFSubjectHelperPtr& subject) {
    for (keto::asn1::RDFPredicateHelperPtr predicateHelper : subject->getPredicates()) {
        for (keto::asn1::RDFObjectHelperPtr objectHelper : predicateHelper->listObjects()) {
            librdf_statement* statement= 0;
            if (objectHelper->getType().compare(keto::asn1::Constants::RDF_NODE::LITERAL) == 0) {
                    statement = librdf_new_statement_from_nodes(this->accountGraphStore->getWorld(), 
                        librdf_new_node_from_uri_string(this->accountGraphStore->getWorld(), (const unsigned char*)subject->getSubject().c_str()),
                        librdf_new_node_from_uri_string(this->accountGraphStore->getWorld(), (const unsigned char*)predicateHelper->getPredicate().c_str()),
                        librdf_new_node_from_typed_literal(
                                this->accountGraphStore->getWorld(), 
                                (const unsigned char*)objectHelper->getValue().c_str(),
                                NULL, 
                                librdf_new_uri(
                                    this->accountGraphStore->getWorld(),
                                    (const unsigned char*)objectHelper->getDataType().c_str()))
                        );
            } else if (objectHelper->getType().compare(keto::asn1::Constants::RDF_NODE::URI) == 0) {
                    statement= librdf_new_statement_from_nodes(this->accountGraphStore->getWorld(), 
                        librdf_new_node_from_uri_string(this->accountGraphStore->getWorld(), (const unsigned char*)subject->getSubject().c_str()),
                        librdf_new_node_from_uri_string(this->accountGraphStore->getWorld(), (const unsigned char*)predicateHelper->getPredicate().c_str()),
                        librdf_new_node_from_uri_string(this->accountGraphStore->getWorld(), (const unsigned char*)objectHelper->getValue().c_str())
                        );
            } else {
                std::stringstream ss;
                ss << "The rdf format [" << objectHelper->getType() << "] is currently not supported";
                BOOST_THROW_EXCEPTION(keto::account_db::UnsupportedDataTypeTransactionException(
                        ss.str()));
            }
            librdf_model_remove_statement(this->accountGraphStore->getModel(), statement);

             /* Free what we just used to add to the model - now it should be stored */
            librdf_free_statement(statement);
        }
    }
}

std::string AccountGraphSession::query(const std::string& queryStr) {
    librdf_query* query;
    librdf_query_results* results;
    query = librdf_new_query(this->accountGraphStore->getWorld(), "sparql", 
            NULL, (const unsigned char *)queryStr.c_str(), NULL);
    results = librdf_model_query_execute(this->accountGraphStore->getModel(), query);
    if (!results) {
        librdf_free_query(query);
        return "NA";
    }
    unsigned char* strBuffer = librdf_query_results_to_string2(results,"json",NULL,NULL,NULL);
    if (!strBuffer) {
        librdf_free_query_results(results);
        librdf_free_query(query);
        return "NA";
    }
    std::string strResult((const char*)strBuffer);
    
    librdf_free_memory(strBuffer);
    librdf_free_query_results(results);
    librdf_free_query(query);
    
    return strResult;
}


AccountGraphSession::AccountGraphSession(const AccountGraphStorePtr& accountGraphStore) :
    activeTransaction(true), accountGraphStore(accountGraphStore) {
    
    if (librdf_model_transaction_start(this->accountGraphStore->getModel())) {
        // the current back end store does not support transactions
        this->activeTransaction = false;
        KETO_LOG_WARNING << "Bankend store for this model does not support transactions : "  << this->accountGraphStore->getDbName();
    }
}

void AccountGraphSession::commit() {
    if (this->activeTransaction) {
        if (librdf_model_transaction_commit(this->accountGraphStore->getModel()) ) {
            std::stringstream ss;
            ss << "Failed to commit graph transaction for [" << accountGraphStore->getDbName() << "]";
            BOOST_THROW_EXCEPTION(keto::account_db::FailedToCommitGraphTransactionException(
                    ss.str()));
        }
        this->activeTransaction = false;
    }
}

void AccountGraphSession::rollback() {
    if (this->activeTransaction) {
        if (librdf_model_transaction_rollback(this->accountGraphStore->getModel()) ) {
            std::stringstream ss;
            ss << "Failed to rollback graph transaction for [" << accountGraphStore->getDbName() << "]";
            BOOST_THROW_EXCEPTION(keto::account_db::FailedToRollbackGraphTransactionException(
                    ss.str()));
        }
        this->activeTransaction = false;
    }
}


}
}