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

#include "keto/wavm_common/WavmSession.hpp"

namespace keto {
namespace wavm_common {

WavmSession::WavmSession(const keto::proto::SandboxCommandMessage& sandboxCommandMessage) :
    sandboxCommandMessage(sandboxCommandMessage) {
    transactionProtoHelper.setTransaction(sandboxCommandMessage.transaction());
    transactionMessageHelperPtr = transactionProtoHelper.getTransactionMessageHelper();
    rdfSessionPtr = std::make_shared<RDFMemorySession>();
    
}

WavmSession::~WavmSession() {
    
}


keto::asn1::ChangeSetHelper WavmSession::getChangeSet() {
    
}


keto::proto::SandboxCommandMessage WavmSession::getSandboxCommandMessage() {
    return this->sandboxCommandMessage;
}



}
}
