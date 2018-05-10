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

#include "Sandbox.pb.h"

#include "keto/asn1/ChangeSetHelper.hpp"
#include "keto/wavm_common/RDFMemorySession.hpp"
#include "keto/transaction_common/TransactionProtoHelper.hpp"



namespace keto {
namespace wavm_common {

class WavmSession;
typedef std::shared_ptr<WavmSession> WavmSessionPtr;

class WavmSession {
public:
    WavmSession(const keto::proto::SandboxCommandMessage& sandboxCommandMessage);
    WavmSession(const WavmSession& orig) = delete;
    virtual ~WavmSession();
    
    
    keto::asn1::ChangeSetHelper getChangeSet();
    keto::proto::SandboxCommandMessage getSandboxCommandMessage();
    
private:
    keto::transaction_common::TransactionProtoHelper transactionProtoHelper;
    keto::transaction_common::TransactionMessageHelperPtr transactionMessageHelperPtr; 
    keto::proto::SandboxCommandMessage sandboxCommandMessage;
    RDFMemorySessionPtr rdfSessionPtr;
};


}
}



#endif /* WAVMSESSION_HPP */

