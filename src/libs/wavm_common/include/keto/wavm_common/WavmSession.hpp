/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   WavmSession.hpp
 * Author: ubuntu
 *
 * Created on May 3, 2018, 2:05 PM
 */

#ifndef WAVMSESSION_HPP
#define WAVMSESSION_HPP

#include <memory>
#include <string>
#include <cstdlib>

#include "Sandbox.pb.h"

#include "keto/asn1/ChangeSetHelper.hpp"
#include "keto/asn1/RDFSubjectHelper.hpp"
#include "keto/asn1/RDFModelHelper.hpp"
#include "keto/asn1/RDFObjectHelper.hpp"
#include "keto/asn1/NumberHelper.hpp"
#include "keto/wavm_common/RDFMemorySession.hpp"
#include "keto/transaction_common/TransactionProtoHelper.hpp"
#include "keto/crypto/KeyLoader.hpp"


namespace keto {
namespace wavm_common {

class WavmSession;
typedef std::shared_ptr<WavmSession> WavmSessionPtr;

class WavmSession {
public:
    WavmSession(const keto::proto::SandboxCommandMessage& sandboxCommandMessage,
            const keto::crypto::KeyLoaderPtr& keyLoaderPtr);
    WavmSession(const WavmSession& orig) = delete;
    virtual ~WavmSession();
    
    // the contract facade methods
    std::string getAccount();
    std::string getTransaction();
    keto::asn1::NumberHelper getTransactionValue();
    keto::asn1::NumberHelper getTransactionFee();
    
    // request methods
    long getRequestModelTransactionValue(
        const std::string& accountModel,
        const std::string& transactionValueModel);
    
    std::string getRequestStringValue(const std::string& subject, const std::string& predicate);
    long getRequestLongValue(const std::string& subject, const std::string& predicate);
    float getRequestFloatValue(const std::string& subject, const std::string& predicate);
    bool getRequestBooleanValue(const std::string& subject, const std::string& predicate);
    
    
    // the common methods used on the session
    void createDebitEntry(const std::string& accountModel, const std::string& transactionValueModel,
            const keto::asn1::NumberHelper& value);
    void createCreditEntry(const std::string& accountModel, const std::string& transactionValueModel,
            const keto::asn1::NumberHelper& value);
    void setResponseStringValue(const std::string& subject, const std::string& predicate,
            const std::string& value);
    void setResponseLongValue(const std::string& subject, const std::string& predicate,
            const long value);
    void setResponseFloatValue(const std::string& subject, const std::string& predicate,
            const float value);
    void setResponseBooleanValue(const std::string& subject, const std::string& predicate,
            const bool value);
    
    
    // the methods used at the end of call to get the change set and sandbox
    keto::proto::SandboxCommandMessage getSandboxCommandMessage();
    
private:
    keto::transaction_common::TransactionProtoHelper transactionProtoHelper;
    keto::transaction_common::TransactionMessageHelperPtr transactionMessageHelperPtr; 
    keto::proto::SandboxCommandMessage sandboxCommandMessage;
    RDFMemorySessionPtr rdfSessionPtr;
    keto::asn1::RDFModelHelper modelHelper;
    keto::crypto::KeyLoaderPtr keyLoaderPtr;
    
    
    keto::asn1::RDFSubjectHelperPtr getSubject(const std::string& subjectUrl);
    keto::asn1::RDFPredicateHelperPtr getPredicate(
        keto::asn1::RDFSubjectHelperPtr subject, const std::string& predicateUrl);
    void addModelEntry(const std::string& subjectUrl, const std::string predicateUrl,
        const std::string& value);
    void addModelEntry(const std::string& subjectUrl, const std::string predicateUrl,
        const long value);
    void addModelEntry(const std::string& subjectUrl, const std::string predicateUrl,
        const float value);
    void addModelEntry(const std::string& subjectUrl, const std::string predicateUrl,
        const bool value);
    void addDateTimeModelEntry(const std::string& subjectUrl, const std::string predicateUrl,
        const time_t value);
    
    keto::asn1::HashHelper getCurrentAccountHash();
    
};


}
}



#endif /* WAVMSESSION_HPP */

