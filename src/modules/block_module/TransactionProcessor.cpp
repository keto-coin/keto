/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TransactionProcessor.cpp
 * Author: ubuntu
 * 
 * Created on April 2, 2018, 9:00 AM
 */

#include <condition_variable>
#include <iostream>

#include "Sandbox.pb.h"
#include "Contract.pb.h"

#include "keto/block/TransactionProcessor.hpp"
#include "keto/transaction_common/ActionHelper.hpp"
#include "keto/transaction_common/TransactionProtoHelper.hpp"

#include "keto/server_common/EventUtils.hpp"
#include "keto/server_common/Events.hpp"
#include "keto/server_common/EventServiceHelpers.hpp"
#include "keto/server_common/Constants.hpp"


namespace keto {
namespace block {

static TransactionProcessorPtr singleton;

TransactionProcessor::TransactionProcessor() {
}

TransactionProcessor::~TransactionProcessor() {
}

TransactionProcessorPtr TransactionProcessor::init() {
    return singleton = std::make_shared<TransactionProcessor>();
}

void TransactionProcessor::fin() {
    singleton.reset();
}

TransactionProcessorPtr TransactionProcessor::getInstance() {
    return singleton;
}

keto::proto::Transaction TransactionProcessor::processTransaction(keto::proto::Transaction& transaction) {
    keto::transaction_common::TransactionProtoHelper transactionProtoHelper(transaction);
    
    // get the transaction from the account store
    keto::proto::ContractMessage contractMessage;
    contractMessage.set_account_hash(transaction.active_account());
    contractMessage.set_contract_name(keto::server_common::Constants::CONTRACTS::BASE_ACCOUNT_CONTRACT);
    
    contractMessage = 
            keto::server_common::fromEvent<keto::proto::ContractMessage>(
            keto::server_common::processEvent(keto::server_common::toEvent<keto::proto::ContractMessage>(
            keto::server_common::Events::GET_CONTRACT,contractMessage)));
    
    keto::proto::SandboxCommandMessage sandboxCommandMessage;
    sandboxCommandMessage.set_contract(contractMessage.contract());
    sandboxCommandMessage.set_transaction((std::string)transactionProtoHelper);
    
    sandboxCommandMessage = 
            keto::server_common::fromEvent<keto::proto::SandboxCommandMessage>(
            keto::server_common::processEvent(keto::server_common::toEvent<keto::proto::SandboxCommandMessage>(
            keto::server_common::Events::EXECUTE_ACTION_MESSAGE,sandboxCommandMessage)));
    
    
    
    std::cout << "Before looping through the actions" << std::endl; 
    if (transactionProtoHelper.getTransactionMessageHelper() && 
            transactionProtoHelper.getTransactionMessageHelper()->getSignedTransaction() &&
            transactionProtoHelper.getTransactionMessageHelper()->getSignedTransaction()->getTransaction()) {
        std::vector<keto::transaction_common::ActionHelperPtr> actions = 
            transactionProtoHelper.getTransactionMessageHelper()->getSignedTransaction()->getTransaction()->getActions();    
        for (keto::transaction_common::ActionHelperPtr action : actions) {
            std::cout << "The action is contract : " << action->getContract().getHash(keto::common::HEX) << std::endl;
        }
        
    }
    
    //transactionProtoHelper.getTransactionMessageHelper()
    return transactionProtoHelper;
}


}
}