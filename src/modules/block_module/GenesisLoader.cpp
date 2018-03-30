/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GenesisLoader.cpp
 * Author: ubuntu
 * 
 * Created on March 8, 2018, 10:02 AM
 */

#include <iostream>
#include <string>
#include <memory>
#include <nlohmann/json.hpp>

#include <botan/pkcs8.h>
#include <botan/hash.h>
#include <botan/data_src.h>
#include <botan/pubkey.h>
#include <botan/rng.h>
#include <botan/auto_rng.h>
#include <botan/hex.h>

#include "Status.h"
#include "BlockChain.pb.h"

#include "keto/common/Log.hpp"

#include "keto/environment/EnvironmentManager.hpp"
#include "keto/environment/Config.hpp"

#include "keto/block/GenesisLoader.hpp"
#include "keto/block/Exception.hpp"
#include "keto/block/Constants.hpp"

#include "keto/asn1/RDFObjectHelper.hpp"
#include "keto/asn1/RDFPredicateHelper.hpp"
#include "keto/asn1/RDFSubjectHelper.hpp"
#include "keto/asn1/RDFModelHelper.hpp"

#include "keto/transaction_common/TransactionMessageHelper.hpp"
#include "keto/transaction_common/ChangeSetBuilder.hpp"
#include "keto/transaction_common/SignedChangeSetBuilder.hpp"
#include "keto/transaction_common/TransactionProtoHelper.hpp"

#include "keto/block_db/BlockBuilder.hpp"
#include "keto/block_db/SignedBlockBuilder.hpp"
#include "keto/block_db/BlockChainStore.hpp"

#include "keto/chain_common/ActionBuilder.hpp"
#include "keto/chain_common/TransactionBuilder.hpp"
#include "keto/chain_common/SignedTransactionBuilder.hpp"

#include "keto/block/Constants.hpp"
#include "keto/block/GenesisLoader.hpp"

#include "keto/server_common/EventUtils.hpp"
#include "keto/server_common/Events.hpp"
#include "keto/server_common/EventServiceHelpers.hpp"

namespace keto {
namespace block {

GenesisLoader::GenesisLoader(const GenesisReader& reader) : reader(reader) {
    std::shared_ptr<keto::environment::Config> config = 
            keto::environment::EnvironmentManager::getInstance()->getConfig();
    if (!config->getVariablesMap().count(Constants::PRIVATE_KEY)) {
        BOOST_THROW_EXCEPTION(keto::block::PrivateKeyNotConfiguredException());
    }
    std::string privateKeyPath = 
            config->getVariablesMap()[Constants::PRIVATE_KEY].as<std::string>();
    if (!config->getVariablesMap().count(Constants::PUBLIC_KEY)) {
        BOOST_THROW_EXCEPTION(keto::block::PrivateKeyNotConfiguredException());
    }
    std::string publicKeyPath = 
            config->getVariablesMap()[Constants::PUBLIC_KEY].as<std::string>();
    keyLoaderPtr = std::make_shared<keto::crypto::KeyLoader>(privateKeyPath,
            publicKeyPath);
    
}

GenesisLoader::GenesisLoader(const GenesisLoader& orig) : reader(orig.reader) {
}

GenesisLoader::~GenesisLoader() {
}

void GenesisLoader::load() {
    keto::asn1::HashHelper parentHash(reader.getJsonData()["parent"],keto::common::HEX);
    
    KETO_LOG_INFO << "Value : "  << parentHash.getHash(keto::common::HEX);
    nlohmann::json transactions = reader.getJsonData()["transactions"].get<nlohmann::json>();
    
    keto::block_db::BlockBuilderPtr blockBuilderPtr = 
            std::make_shared<keto::block_db::BlockBuilder>(parentHash);
    for (auto& element : transactions) {
        keto::asn1::HashHelper sourceAccount(element["account_hash"].get<std::string>().c_str(),keto::common::HEX);
        KETO_LOG_INFO << "Account hash : " << sourceAccount.getHash(keto::common::HEX);
        keto::asn1::NumberHelper numberHelper(
            atol(element["value"].get<std::string>().c_str()));
        std::shared_ptr<keto::chain_common::TransactionBuilder> transactionPtr =
            keto::chain_common::TransactionBuilder::createTransaction();
        transactionPtr->setParent(parentHash).setSourceAccount(sourceAccount)
                .setTargetAccount(sourceAccount).setValue(numberHelper);
        
        //std::cout << element << '\n';
        //std::cout << "Account hash : "  << element["account_hash"] << std::endl;
        //std::cout << "Public Key : "  << element["public_key"] << std::endl;
        nlohmann::json model = element["model"].get<nlohmann::json>();
        keto::asn1::RDFModelHelper modelHelper;
        for (nlohmann::json& element2 : model["rdf"]) {
            //std::cout << "Change set : "  << element2 << std::endl;
            for (nlohmann::json::iterator it = element2.begin(); it != element2.end(); ++it) {
                nlohmann::json predicate = it.value();
                keto::asn1::RDFSubjectHelper subjectHelper(it.key()); 
                KETO_LOG_INFO << "key : " << it.key() << " : [" << predicate << "]";
                for (nlohmann::json::iterator predIter = predicate.begin(); predIter != predicate.end(); ++predIter) {
                    keto::asn1::RDFPredicateHelper predicateHelper(predIter.key()); 
                    KETO_LOG_INFO << "key : " << predIter.key();
                    nlohmann::json contentWrapper = predIter.value();
                    KETO_LOG_INFO << "Content wrapper" << contentWrapper;
                    nlohmann::json jsonObj = contentWrapper.begin().value();
                    KETO_LOG_INFO << "Json object" << jsonObj;
                    keto::asn1::RDFObjectHelper objectHelper;
                    objectHelper.setDataType(jsonObj["datatype"].get<std::string>()).
                    setType(jsonObj["type"].get<std::string>()).
                    setValue(jsonObj["value"].get<std::string>());
                    KETO_LOG_INFO << "Add object to predicate";
                    predicateHelper.addObject(objectHelper);
                    subjectHelper.addPredicate(predicateHelper);
                }
                modelHelper.addSubject(subjectHelper);
            }
        }
        keto::asn1::AnyHelper anyModel(modelHelper);
        std::shared_ptr<keto::chain_common::ActionBuilder> actionBuilderPtr =
                keto::chain_common::ActionBuilder::createAction();
        actionBuilderPtr->setModel(anyModel);
        transactionPtr->addAction(actionBuilderPtr);
        
        
        KETO_LOG_INFO << "Memory data source private key " << element["private_key"].get<std::string>();
        KETO_LOG_INFO << "Memory data source private key " << Botan::hex_encode(
            Botan::hex_decode_locked(element["private_key"].get<std::string>(),false),true);
        keto::asn1::PrivateKeyHelper privateKeyHelper(element["private_key"].get<std::string>(),keto::common::HEX);
        KETO_LOG_INFO << "Signed transaction builder";
        std::shared_ptr<keto::chain_common::SignedTransactionBuilder> signedTransBuild = 
            keto::chain_common::SignedTransactionBuilder::createTransaction(
                privateKeyHelper);
        KETO_LOG_INFO << "Sign transaction" << std::endl;
        signedTransBuild->setTransaction(transactionPtr).sign();
        keto::transaction_common::TransactionMessageHelperPtr transactionMessageHelper(
            new keto::transaction_common::TransactionMessageHelper(signedTransBuild->operator SignedTransaction*()));
        transactionMessageHelper->setStatus(Status_complete).setSourceAccount(sourceAccount).setTargetAccount(sourceAccount);
        
        
        // create a change set set
        keto::transaction_common::ChangeSetBuilderPtr changeSetBuilder(
            new keto::transaction_common::ChangeSetBuilder(
                transactionMessageHelper->getHash(),
                sourceAccount));
        changeSetBuilder->addChange(anyModel).setStatus(Status_complete);
        keto::transaction_common::SignedChangeSetBuilderPtr signedChangeSetBuilder(new
            keto::transaction_common::SignedChangeSetBuilder(*changeSetBuilder,*keyLoaderPtr));
        signedChangeSetBuilder->sign();
        
        transactionMessageHelper->addChangeSet(*signedChangeSetBuilder);
        
        keto::transaction_common::TransactionProtoHelper transactionProtoHelper(
                transactionMessageHelper);
        transactionProtoHelper = 
            keto::server_common::fromEvent<keto::proto::Transaction>(
            keto::server_common::processEvent(keto::server_common::toEvent<keto::proto::Transaction>(
            keto::server_common::Events::APPLY_ACCOUNT_TRANSACTION_MESSAGE,transactionProtoHelper)));
        
        blockBuilderPtr->addTransactionMessage(*transactionProtoHelper.getTransactionMessageHelper());
    }
    
    keto::block_db::SignedBlockBuilderPtr signedBlockBuilderPtr(new keto::block_db::SignedBlockBuilder(
            blockBuilderPtr->operator Block_t*(),
            keyLoaderPtr));
    signedBlockBuilderPtr->sign();
    
    KETO_LOG_INFO << "Create the genesis BLOCK";
    keto::block_db::BlockChainStore::getInstance()->writeBlock(*signedBlockBuilderPtr);
    KETO_LOG_INFO << "Created the genesis BLOCK";
        
}




}
}
