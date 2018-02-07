/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#define BOOST_TEST_MODULE ChainCommonsTest

#include <thread>         // std::this_thread::sleep_for
#include <chrono>

#include <botan/hash.h>
#include <botan/rsa.h>
#include <botan/rng.h>
#include <botan/p11_randomgenerator.h>
#include <botan/auto_rng.h>
#include <botan/pkcs8.h>
#include <botan/hex.h>

#include <boost/test/unit_test.hpp>
#include <iostream>
#include <botan/x509_key.h>
#include "TestEntity.h"
#include "Number.h"
#include "keto/common/MetaInfo.hpp"
#include "keto/asn1/TimeHelper.hpp"
#include "keto/asn1/SerializationHelper.hpp"
#include "keto/asn1/DeserializationHelper.hpp"

#include "keto/chain_common/TransactionBuilder.hpp"
#include "keto/chain_common/SignedTransactionBuilder.hpp"
#include "keto/chain_common/ActionBuilder.hpp"
#include "keto/crypto/SignatureVerification.hpp"

std::shared_ptr<keto::chain_common::TransactionBuilder> buildTransaction() {
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
    
    return transactionPtr;
}


BOOST_AUTO_TEST_CASE( chain_commons_test ) {
    std::shared_ptr<keto::chain_common::TransactionBuilder> transactionPtr = 
            buildTransaction();
    
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
    
    
    std::unique_ptr<Botan::RandomNumberGenerator> rng(new Botan::AutoSeeded_RNG);
    Botan::RSA_PrivateKey privateKey(*rng.get(), 2048);
    Botan::RSA_PublicKey publicKey(privateKey);
    std::vector<uint8_t> publicKeyVector = Botan::X509::BER_encode(publicKey);
    
    keto::asn1::PrivateKeyHelper privateKeyHelper;
    privateKeyHelper.setKey(
        Botan::PKCS8::BER_encode( privateKey ));
    
    std::shared_ptr<keto::chain_common::SignedTransactionBuilder> signedTransBuild = 
            keto::chain_common::SignedTransactionBuilder::createTransaction(
                privateKeyHelper);
    signedTransBuild->setTransaction(transactionPtr);
    signedTransBuild->sign();
    
    std::cout << "The sha is [" << string256 << "]" << std::endl;
    std::cout << "The sha is [" << signedTransBuild->getHash() << "]" << std::endl;
    std::cout << "The signature is [" << signedTransBuild->getSignature() << "]" << std::endl;
    
    std::this_thread::sleep_for (std::chrono::seconds(1));
    
    std::shared_ptr<keto::chain_common::SignedTransactionBuilder> signedTransBuild2 = 
            keto::chain_common::SignedTransactionBuilder::createTransaction(
                privateKeyHelper);
    signedTransBuild2->setTransaction(buildTransaction());
    signedTransBuild2->sign();
    
    //std::cout << "The sha is [" << string256 << "]" << std::endl;
    std::cout << "The sha is [" << signedTransBuild2->getHash() << "]" << std::endl;
    std::cout << "The signature is [" << signedTransBuild2->getSignature() << "]" << std::endl;
    
    keto::crypto::SecureVector hashBytes = Botan::hex_decode_locked(signedTransBuild2->getHash(),true);
    std::vector<uint8_t> signatureBytes = Botan::hex_decode(signedTransBuild2->getSignature(),true);
    
    std::cout << "Validation says " << keto::crypto::SignatureVerification(publicKeyVector,hashBytes).check(
            signatureBytes) << std::endl;
    BOOST_CHECK(keto::crypto::SignatureVerification(publicKeyVector,hashBytes).check(
            signatureBytes));
}