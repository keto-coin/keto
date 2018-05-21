/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   WavmSession.cpp
 * Author: ubuntu
 * 
 * Created on May 3, 2018, 2:05 PM
 */

#include <cstdlib>

#include "RDFChange.h"

#include "keto/server_common/Constants.hpp"
#include "keto/wavm_common/WavmSession.hpp"
#include "keto/wavm_common/RDFURLUtils.hpp"
#include "keto/wavm_common/RDFConstants.hpp"
#include "include/keto/wavm_common/RDFConstants.hpp"
#include "include/keto/wavm_common/RDFURLUtils.hpp"
#include "keto/wavm_common/Exception.hpp"

#include "keto/environment/EnvironmentManager.hpp"
#include "keto/environment/Config.hpp"

#include "keto/transaction_common/TransactionMessageHelper.hpp"
#include "keto/transaction_common/ChangeSetBuilder.hpp"
#include "keto/transaction_common/SignedChangeSetBuilder.hpp"
#include "keto/transaction_common/TransactionProtoHelper.hpp"

namespace keto {
namespace wavm_common {

WavmSession::WavmSession(const keto::proto::SandboxCommandMessage& sandboxCommandMessage,
        const keto::crypto::KeyLoaderPtr& keyLoaderPtr) : 
    sandboxCommandMessage(sandboxCommandMessage) , modelHelper(RDFChange_persist),
        keyLoaderPtr(keyLoaderPtr) {
    transactionProtoHelper.setTransaction(sandboxCommandMessage.transaction());
    transactionMessageHelperPtr = transactionProtoHelper.getTransactionMessageHelper();
    rdfSessionPtr = std::make_shared<RDFMemorySession>();
    
}

WavmSession::~WavmSession() {
    
}

// the contract facade methods
std::string WavmSession::getAccount() {
    return getCurrentAccountHash().getHash(keto::common::StringEncoding::HEX);
}

std::string WavmSession::getTransaction() {
    return transactionMessageHelperPtr->getSignedTransaction()->getHash().getHash(keto::common::StringEncoding::HEX);
}

Status WavmSession::getStatus() {
    return transactionMessageHelperPtr->getStatus();
}

keto::asn1::NumberHelper WavmSession::getTransactionValue() {
    return transactionMessageHelperPtr->getSignedTransaction()->getTransaction()->getValue();
}

keto::asn1::NumberHelper WavmSession::getTransactionFee() {
    keto::asn1::NumberHelper numberHelper((const long)0);
    return numberHelper;
}

// request methods
long WavmSession::getRequestModelTransactionValue(
    const std::string& accountModel,
    const std::string& transactionValueModel) {
    keto::wavm_common::RDFURLUtils transactionUrl(transactionValueModel);
    std::string transactionId = getTransaction();
    return rdfSessionPtr->getLongValue(transactionUrl.buildSubjectUrl(transactionId),
            transactionUrl.buildPredicateUrl(RDFConstants::ACCOUNT_TRANSACTION_SUBJECTS::VALUE));
}

std::string WavmSession::getRequestStringValue(const std::string& subject, 
        const std::string& predicate) {
    return rdfSessionPtr->getStringValue(subject,predicate);
}

long WavmSession::getRequestLongValue(const std::string& subject, 
        const std::string& predicate) {
    return rdfSessionPtr->getLongValue(subject,predicate);
}

float WavmSession::getRequestFloatValue(const std::string& subject,
        const std::string& predicate) {
    return rdfSessionPtr->getFloatValue(subject,predicate);
}

bool WavmSession::getRequestBooleanValue(const std::string& subject,
        const std::string& predicate) {
    return rdfSessionPtr->getBooleanValue(subject,predicate);
}



void WavmSession::createDebitEntry(const std::string& accountModel, const std::string& transactionValueModel,
        const keto::asn1::NumberHelper& value) {
    keto::wavm_common::RDFURLUtils accountUrl(accountModel);
    keto::wavm_common::RDFURLUtils transactionUrl(transactionValueModel);
    std::string id = this->getTransaction();
    std::string hash = this->getAccount();
    std::string subjectUrl = transactionUrl.buildSubjectUrl(id);
    this->addModelEntry(
        subjectUrl,transactionUrl.buildPredicateUrl(RDFConstants::ACCOUNT_TRANSACTION_SUBJECTS::ID),id);
    this->addDateTimeModelEntry(
        subjectUrl,transactionUrl.buildPredicateUrl(RDFConstants::ACCOUNT_TRANSACTION_SUBJECTS::DATE_TIME),time(0));
    this->addModelEntry(
        subjectUrl,transactionUrl.buildPredicateUrl(RDFConstants::ACCOUNT_TRANSACTION_SUBJECTS::TYPE),
            keto::server_common::Constants::Constants::ACCOUNT_ACTIONS::DEBIT);
    this->addModelEntry(
        subjectUrl,transactionUrl.buildPredicateUrl(RDFConstants::ACCOUNT_TRANSACTION_SUBJECTS::ACCOUNT_HASH),
            hash);
    this->addModelEntry(
        subjectUrl,transactionUrl.buildPredicateUrl(RDFConstants::ACCOUNT_TRANSACTION_SUBJECTS::VALUE),
            value.operator long());
    
}

void WavmSession::createCreditEntry(const std::string& accountModel, const std::string& transactionValueModel,
        const keto::asn1::NumberHelper& value) {
    keto::wavm_common::RDFURLUtils accountUrl(accountModel);
    keto::wavm_common::RDFURLUtils transactionUrl(transactionValueModel);
    std::string id = this->getTransaction();
    std::string hash = this->getAccount();
    std::string subjectUrl = transactionUrl.buildSubjectUrl(id);
    this->addModelEntry(
        subjectUrl,transactionUrl.buildPredicateUrl(RDFConstants::ACCOUNT_TRANSACTION_SUBJECTS::ID),id);
    this->addDateTimeModelEntry(
        subjectUrl,transactionUrl.buildPredicateUrl(RDFConstants::ACCOUNT_TRANSACTION_SUBJECTS::DATE_TIME),time(0));
    this->addModelEntry(
        subjectUrl,transactionUrl.buildPredicateUrl(RDFConstants::ACCOUNT_TRANSACTION_SUBJECTS::TYPE),
            keto::server_common::Constants::Constants::ACCOUNT_ACTIONS::CREDIT);
    this->addModelEntry(
        subjectUrl,transactionUrl.buildPredicateUrl(RDFConstants::ACCOUNT_TRANSACTION_SUBJECTS::ACCOUNT_HASH),
            hash);
    this->addModelEntry(
        subjectUrl,transactionUrl.buildPredicateUrl(RDFConstants::ACCOUNT_TRANSACTION_SUBJECTS::VALUE),
            value.operator long());
    
}

void WavmSession::setResponseStringValue(const std::string& subject, const std::string& predicate,
        const std::string& value) {
    this->addModelEntry(subject,predicate,value);
}

void WavmSession::setResponseLongValue(const std::string& subject, const std::string& predicate,
        const long value) {
    this->addModelEntry(subject,predicate,value);
}

void WavmSession::setResponseFloatValue(const std::string& subject, const std::string& predicate,
        const float value) {
    this->addModelEntry(subject,predicate,value);
}

void WavmSession::setResponseBooleanValue(const std::string& subject, const std::string& predicate,
        const bool value) {
    this->addBooleanModelEntry(subject,predicate,value);
}


keto::proto::SandboxCommandMessage WavmSession::getSandboxCommandMessage() {
    // create a change and add it to the transaction
    keto::asn1::AnyHelper anyModel(this->modelHelper);
    keto::transaction_common::ChangeSetBuilderPtr changeSetBuilder(
        new keto::transaction_common::ChangeSetBuilder(
            transactionMessageHelperPtr->getSignedTransaction()->getHash(),
            this->getCurrentAccountHash()));
    changeSetBuilder->addChange(anyModel).setStatus(transactionMessageHelperPtr->getStatus());
    keto::transaction_common::SignedChangeSetBuilderPtr signedChangeSetBuilder(new
        keto::transaction_common::SignedChangeSetBuilder(*changeSetBuilder,*keyLoaderPtr));
    signedChangeSetBuilder->sign();
    transactionMessageHelperPtr->addChangeSet(*signedChangeSetBuilder);
    
    // set the the transaction
    keto::transaction_common::TransactionProtoHelper transactionProtoHelper(
                transactionMessageHelperPtr);
    sandboxCommandMessage.set_transaction(transactionProtoHelper.operator std::string());
    
    return this->sandboxCommandMessage;
}


keto::asn1::RDFSubjectHelperPtr WavmSession::getSubject(const std::string& subjectUrl) {
    if (!this->modelHelper.contains(subjectUrl)) {
        keto::asn1::RDFSubjectHelper subject(subjectUrl);
        this->modelHelper.addSubject(subject);
    }
    return this->modelHelper[subjectUrl];
}

keto::asn1::RDFPredicateHelperPtr WavmSession::getPredicate(
    keto::asn1::RDFSubjectHelperPtr subject, const std::string& predicateUrl) {
    if (!subject->containsPredicate(predicateUrl)) {
        keto::asn1::RDFPredicateHelper predicate(predicateUrl);
        subject->addPredicate(predicate);
    }
    return subject->operator [](predicateUrl);
}

void WavmSession::addModelEntry(const std::string& subjectUrl, const std::string predicateUrl,
        const std::string& value) {
    keto::asn1::RDFSubjectHelperPtr subjectHelperPtr = getSubject(subjectUrl);
    keto::asn1::RDFPredicateHelperPtr predicate = getPredicate(subjectHelperPtr,predicateUrl);
    
    keto::asn1::RDFObjectHelper objectHelper;
    objectHelper.setDataType(RDFConstants::TYPES::STRING).
        setType(RDFConstants::NODE_TYPES::LITERAL).
        setValue(value);
    
    predicate->addObject(objectHelper);
    
    rdfSessionPtr->setStringValue(
        subjectUrl,predicateUrl,value);
    
    
}

void WavmSession::addModelEntry(const std::string& subjectUrl, const std::string predicateUrl,
        const long value) {
    keto::asn1::RDFSubjectHelperPtr subjectHelperPtr = getSubject(subjectUrl);
    keto::asn1::RDFPredicateHelperPtr predicate = getPredicate(subjectHelperPtr,predicateUrl);
    
    std::stringstream ss;
    ss << value;
    keto::asn1::RDFObjectHelper objectHelper;
    objectHelper.setDataType(RDFConstants::TYPES::LONG).
        setType(RDFConstants::NODE_TYPES::LITERAL).
        setValue(ss.str());
    
    predicate->addObject(objectHelper);
    
    rdfSessionPtr->setLongValue(
        subjectUrl,predicateUrl,value);
}

void WavmSession::addModelEntry(const std::string& subjectUrl, const std::string predicateUrl,
        const float value) {
    keto::asn1::RDFSubjectHelperPtr subjectHelperPtr = getSubject(subjectUrl);
    keto::asn1::RDFPredicateHelperPtr predicate = getPredicate(subjectHelperPtr,predicateUrl);
    
    std::stringstream ss;
    ss << value;
    keto::asn1::RDFObjectHelper objectHelper;
    objectHelper.setDataType(RDFConstants::TYPES::FLOAT).
        setType(RDFConstants::NODE_TYPES::LITERAL).
        setValue(ss.str());
    
    predicate->addObject(objectHelper);
    
    rdfSessionPtr->setFloatValue(
        subjectUrl,predicateUrl,value);
    
}

void WavmSession::addBooleanModelEntry(const std::string& subjectUrl, const std::string predicateUrl,
        const bool value) {
    keto::asn1::RDFSubjectHelperPtr subjectHelperPtr = getSubject(subjectUrl);
    keto::asn1::RDFPredicateHelperPtr predicate = getPredicate(subjectHelperPtr,predicateUrl);
    
    std::stringstream ss;
    if (value) {
        ss << "true";
    } else {
        ss << "false";
    }
    keto::asn1::RDFObjectHelper objectHelper;
    objectHelper.setDataType(RDFConstants::TYPES::BOOLEAN).
        setType(RDFConstants::NODE_TYPES::LITERAL).
        setValue(ss.str());
    
    predicate->addObject(objectHelper);
    
    rdfSessionPtr->setBooleanValue(
        subjectUrl,predicateUrl,value);
}

void WavmSession::addDateTimeModelEntry(const std::string& subjectUrl, const std::string predicateUrl,
        const time_t value) {
    keto::asn1::RDFSubjectHelperPtr subjectHelperPtr = getSubject(subjectUrl);
    keto::asn1::RDFPredicateHelperPtr predicate = getPredicate(subjectHelperPtr,predicateUrl);
    
    struct tm  tstruct;
    char       buf[80];
    struct tm result;
    localtime_r(&value,&result);
    strftime(buf, sizeof(buf), "%Y-%m-%dT%X", &tstruct);
    
    keto::asn1::RDFObjectHelper objectHelper;
    objectHelper.setDataType(RDFConstants::TYPES::DATE_TIME).
        setType(RDFConstants::NODE_TYPES::LITERAL).
        setValue(buf);
    
    predicate->addObject(objectHelper);
    
    rdfSessionPtr->setDateTimeValue(
        subjectUrl,predicateUrl,value);
}


keto::asn1::HashHelper WavmSession::getCurrentAccountHash() {
    if ((transactionMessageHelperPtr->getStatus() == Status_init) ||
        (transactionMessageHelperPtr->getStatus() == Status_debit)){
        return transactionMessageHelperPtr->getSourceAccount();
    } else if (transactionMessageHelperPtr->getStatus() == Status_credit) {
        return transactionMessageHelperPtr->getTargetAccount();
    } else if (transactionMessageHelperPtr->getStatus() == Status_fee) {      
        return transactionMessageHelperPtr->getFeeAccount();
    }
    std::stringstream ss;
    ss << "Unrecognised status [" << transactionMessageHelperPtr->getStatus() << "]";
    BOOST_THROW_EXCEPTION(keto::wavm_common::UnrecognisedTransactionStatusException(
                        ss.str()));
}

}
}
