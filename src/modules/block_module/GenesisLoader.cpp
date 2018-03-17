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
#include "keto/block_db/BlockBuilder.hpp"
#include "keto/block_db/SignedBlockBuilder.hpp"
#include "keto/block_db/BlockChainStore.hpp"
#include "keto/chain_common/ActionBuilder.hpp"
#include "keto/chain_common/TransactionBuilder.hpp"
#include "keto/chain_common/SignedTransactionBuilder.hpp"
#include "include/keto/block/Constants.hpp"
#include "include/keto/block/GenesisLoader.hpp"

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
    //std::cout << "Dump : "  << reader.getJsonData().dump() << std::endl;
    //std::cout << "Is object : "  << reader.getJsonData().is_object() << std::endl;
    //std::cout << "Is array : "  << reader.getJsonData().is_array() << std::endl;
    keto::asn1::HashHelper parentHash(reader.getJsonData()["parent"],keto::common::HEX);
    
    std::cout << "Value : "  << parentHash.getHash(keto::common::HEX) << std::endl;
    //std::cout << "Transaction : "  << reader.getJsonData()["transactions"].is_array() << std::endl;
    nlohmann::json transactions = reader.getJsonData()["transactions"].get<nlohmann::json>();
    
    keto::block_db::BlockBuilderPtr blockBuilderPtr = 
            std::make_shared<keto::block_db::BlockBuilder>(parentHash);
    for (auto& element : transactions) {
        keto::asn1::HashHelper sourceAccount(element["account_hash"],keto::common::HEX);
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
                std::cout << "key : " << it.key() << " : [" << predicate << "]" << std::endl;
                for (nlohmann::json::iterator predIter = predicate.begin(); predIter != predicate.end(); ++predIter) {
                    keto::asn1::RDFPredicateHelper predicateHelper(predIter.key()); 
                    std::cout << "key : " << predIter.key() << std::endl;
                    nlohmann::json contentWrapper = predIter.value();
                    std::cout << "Content wrapper" << contentWrapper << std::endl;
                    nlohmann::json jsonObj = contentWrapper.begin().value();
                    std::cout << "Json object" << jsonObj << std::endl;
                    keto::asn1::RDFObjectHelper objectHelper;
                    objectHelper.setDataType(jsonObj["datatype"].get<std::string>()).
                    setType(jsonObj["type"].get<std::string>()).
                    setValue(jsonObj["value"].get<std::string>());
                    std::cout << "Add object to predicate" << std::endl;
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
        
        
        std::cout << "Memory data source private key " << element["private_key"].get<std::string>() << std::endl;
        std::cout << "Memory data source private key " << Botan::hex_encode(
            Botan::hex_decode_locked(element["private_key"].get<std::string>(),false),true) << std::endl;
        keto::asn1::PrivateKeyHelper privateKeyHelper(element["private_key"].get<std::string>(),keto::common::HEX);
        std::cout << "Signed transaction builder" << std::endl;
        std::shared_ptr<keto::chain_common::SignedTransactionBuilder> signedTransBuild = 
            keto::chain_common::SignedTransactionBuilder::createTransaction(
                privateKeyHelper);
        std::cout << "Sign transaction" << std::endl;
        signedTransBuild->setTransaction(transactionPtr).sign();
        keto::transaction_common::TransactionMessageHelper transactionMessageHelper(signedTransBuild->operator SignedTransaction*());
        blockBuilderPtr->addTransactionMessage(transactionMessageHelper);
    }
    
    keto::block_db::SignedBlockBuilderPtr signedBlockBuilderPtr(new keto::block_db::SignedBlockBuilder(
            blockBuilderPtr->operator Block_t*(),
            keyLoaderPtr));
    signedBlockBuilderPtr->sign();
    
    keto::block_db::BlockChainStore::getInstance()->writeBlock(*signedBlockBuilderPtr);
    
    //for (nlohmann::json::iterator iter = reader.getJsonData()["transactions"].begin();
    //    iter != reader.getJsonData()["transactions"].end(); iter++ ) {
    //    nlohmann::json transaction = iter.value().get<nlohmann::json>();
    //    std::cout << "Object : "  << iter->value.is_object() << std::endl;
    //    if (iter->is_object()) {
    //        std::cout << "Account hash : "  << iter.value()["account_hash"] << std::endl;
    //    }
    //}
    
    //std::cout << "Transaction array : " << reader.getJsonData()["transactions"].is_array() << std::endl;
    //for (auto& element : reader.getJsonData()["transactions"]) {
    //    std::cout << "Elements in transaction [" << element << "]" << std::endl;
    //}
    //reader.getJsonData()["transactions"]
    //for (nlohmann::json::iterator iter = reader.getJsonData()["transactions"].begin();
    //        iter != reader.getJsonData()["transactions"].end(); iter++ ) {
    //    std::cout << "Is array : " << iter.value().is_array() << std::endl;
    //    std::cout << "Is boolean" << iter.value().is_boolean() << std::endl;
    //    std::cout << "Is number" << iter.value().is_number() << std::endl;
    //    std::cout << "Is number" << iter.value().is_object() << std::endl;
    //    std::cout << "Is number" << iter.value().is_string() << std::endl;
    //    std::cout << "account hash" << iter.value()["account_hash"].get<std::string>() << std::endl;
    //}
    
        
}




}
}
