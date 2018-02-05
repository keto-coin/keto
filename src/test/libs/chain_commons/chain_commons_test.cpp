/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#define BOOST_TEST_MODULE ChainCommonsTest

#include <botan/hash.h>
#include <boost/test/unit_test.hpp>
#include <iostream>
#include "TestEntity.h"
#include "Number.h"
#include "keto/common/MetaInfo.hpp"
#include "keto/asn1/TimeHelper.hpp"
#include "keto/asn1/SerializationHelper.hpp"
#include "keto/asn1/DeserializationHelper.hpp"

#include "keto/chain_common/TransactionBuilder.hpp"
#include "keto/chain_common/SignedTransactionBuilder.hpp"
#include "keto/chain_common/ActionBuilder.hpp"

BOOST_AUTO_TEST_CASE( chain_commons_test ) {
    
    std::shared_ptr<keto::chain_common::ActionBuilder> actionPtr =
            keto::chain_common::ActionBuilder::createAction();
    actionPtr->setContract(
            keto::asn1::HashHelper("3D89018355E055923478E8E816D82A26A8AA10A2AE5B497847084AB7F54B9238",
                keto::common::HEX)).setParent(
            keto::asn1::HashHelper("3D89018355E055923478E8E816D82A26A8AA10A2AE5B497847084AB7F54B9238",
                keto::common::HEX)).setSourceAccount(
            keto::asn1::HashHelper("3D89018355E055923478E8E816D82A26A8AA10A2AE5B497847084AB7F54B9238",
                keto::common::HEX)).setTargetAccount(
            keto::asn1::HashHelper("3D89018355E055923478E8E816D82A26A8AA10A2AE5B497847084AB7F54B9238",
                keto::common::HEX)).setValue(keto::asn1::NumberHelper(30));
    
    std::shared_ptr<keto::chain_common::ActionBuilder> actionPtr2 =
            keto::chain_common::ActionBuilder::createAction();
    actionPtr2->setContract(
            keto::asn1::HashHelper("3D89018355E055923478E8E816D82A26A8AA10A2AE5B497847084AB7F54B9238",
                keto::common::HEX)).setParent(
            keto::asn1::HashHelper("3D89018355E055923478E8E816D82A26A8AA10A2AE5B497847084AB7F54B9238",
                keto::common::HEX)).setSourceAccount(
            keto::asn1::HashHelper("3D89018355E055923478E8E816D82A26A8AA10A2AE5B497847084AB7F54B9238",
                keto::common::HEX)).setTargetAccount(
            keto::asn1::HashHelper("3D89018355E055923478E8E816D82A26A8AA10A2AE5B497847084AB7F54B9238",
                keto::common::HEX)).setValue(keto::asn1::NumberHelper(40));
    
    
    std::shared_ptr<keto::chain_common::TransactionBuilder> transactionPtr =
        keto::chain_common::TransactionBuilder::createTransaction();
    transactionPtr->setParent(
            keto::asn1::HashHelper("3D89018355E055923478E8E816D82A26A8AA10A2AE5B497847084AB7F54B9238",
        keto::common::HEX)).setSourceAccount(
            keto::asn1::HashHelper("3D89018355E055923478E8E816D82A26A8AA10A2AE5B497847084AB7F54B9238",
        keto::common::HEX)).setTargetAccount(
            keto::asn1::HashHelper("3D89018355E055923478E8E816D82A26A8AA10A2AE5B497847084AB7F54B9238",
        keto::common::HEX)).setValue(keto::asn1::NumberHelper(20)).addAction(actionPtr).addAction(actionPtr2);
    
    xer_fprint(stdout, &asn_DEF_Transaction, transactionPtr->getPtr());
    
    std::vector<uint8_t> transactionBytes = transactionPtr->operator std::vector<uint8_t>&();
    
    std::cout << "The transaction bytes are [" << transactionBytes.size() << "]" << std::endl;
    keto::asn1::DeserializationHelper<Transaction> deserializeHelper(
            transactionBytes,&asn_DEF_Transaction);
    
    Transaction* transaction = (Transaction*)deserializeHelper;
    xer_fprint(stdout, &asn_DEF_Transaction, transaction);
    
    std::unique_ptr<Botan::HashFunction> hash256(Botan::HashFunction::create("SHA-256"));
    keto::crypto::SecureVector vector256 = 
            hash256->process(transactionPtr->operator std::vector<uint8_t>&());
    keto::asn1::HashHelper hashHelper256(vector256);
    std::string string256 = hashHelper256.getHash(keto::common::HEX);
    
    std::shared_ptr<keto::chain_common::SignedTransactionBuilder> signedTransBuild = 
            keto::chain_common::SignedTransactionBuilder::createTransaction(
                keto::crypto::PrivateKeyHelper());
    signedTransBuild->setTransaction(transactionPtr);
    
    std::cout << "The sha is [" << string256 << "]" << std::endl;
    std::cout << "The sha is [" << signedTransBuild->getHash() << "]" << std::endl;
    
}