/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#define BOOST_TEST_MODULE ChainCommonsTest
#include <boost/test/unit_test.hpp>
#include <iostream>
#include "TestEntity.h"
#include "Number.h"
#include "keto/common/MetaInfo.hpp"
#include "keto/asn1/TimeHelper.hpp"
#include "keto/asn1/SerializationHelper.hpp"
#include "keto/asn1/DeserializationHelper.hpp"

#include "keto/chain_common/TransactionBuilder.hpp"
#include "keto/chain_common/ActionBuilder.hpp"

BOOST_AUTO_TEST_CASE( chain_commons_test ) {

    std::vector<uint8_t> transactionBytes = 
    keto::chain_common::TransactionBuilder::createTransaction()->setParent(
            keto::asn1::HashHelper("3D89018355E055923478E8E816D82A26A8AA10A2AE5B497847084AB7F54B9238",
        keto::common::HEX)).setSourceAccount(
            keto::asn1::HashHelper("3D89018355E055923478E8E816D82A26A8AA10A2AE5B497847084AB7F54B9238",
        keto::common::HEX)).setTargetAccount(
            keto::asn1::HashHelper("3D89018355E055923478E8E816D82A26A8AA10A2AE5B497847084AB7F54B9238",
        keto::common::HEX)).setValue(keto::asn1::NumberHelper(20)).operator std::vector<uint8_t>&();
    
    keto::asn1::DeserializationHelper<Transaction> deserializeHelper(
            transactionBytes,&asn_DEF_Transaction);
    
    Transaction* transaction = (Transaction*)deserializeHelper;
    xer_fprint(stdout, &asn_DEF_Transaction, transaction);
}