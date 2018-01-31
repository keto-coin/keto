/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#define BOOST_TEST_MODULE AsnTest
#include <boost/test/unit_test.hpp>
#include <iostream>
#include "Transaction.h"
#include "keto/common/MetaInfo.hpp"
#include "keto/asn1/TimeHelper.hpp"
#include "keto/asn1/SerializationHelper.hpp"
#include "keto/asn1/DeserializationHelper.hpp"



BOOST_AUTO_TEST_CASE( asn1_test ) {
    // test the time helper
    keto::asn1::TimeHelper timeHelper1;
    keto::asn1::TimeHelper timeHelper2;
    
    // this performs a slice
    timeHelper2 = (UTCTime_t*)timeHelper1;
    timeHelper1 = (UTCTime_t*)timeHelper2;
    
    std::cout << "The duration is : " << ((std::chrono::system_clock::time_point)timeHelper2).time_since_epoch().count() << std::endl;
    std::cout << "The duration is : " << ((std::chrono::system_clock::time_point)timeHelper1).time_since_epoch().count() << std::endl;
    
    BOOST_CHECK( ((std::chrono::system_clock::time_point)timeHelper2).time_since_epoch().count() == 
            ((std::chrono::system_clock::time_point)timeHelper1).time_since_epoch().count() );
    
    
    // instanciate a transaction
    Transaction* transaction = (Transaction*)calloc(1, sizeof *transaction);
    transaction->version = keto::common::MetaInfo::PROTOCOL_VERSION;
    transaction->date = *(UTCTime_t*)keto::asn1::TimeHelper();
    //xer_fprint(stdout, &asn_DEF_Transaction, transaction);
    
    unsigned char* buffer = (unsigned char*)keto::asn1::SerializationHelper<Transaction>(transaction,&asn_DEF_Transaction);
    keto::asn1::DeserializationHelper<Transaction> deserializeHelper(
            buffer,&asn_DEF_Transaction);
    Transaction* transaction2 = (Transaction*)deserializeHelper;
    //xer_fprint(stdout, &asn_DEF_Transaction, transaction2);
    
    timeHelper1 = &transaction->date;
    timeHelper2 = &transaction2->date;
    
    BOOST_CHECK( ((std::chrono::system_clock::time_point)timeHelper2).time_since_epoch().count() == 
            ((std::chrono::system_clock::time_point)timeHelper1).time_since_epoch().count() );
    
    free(buffer);
    
    std::vector<unsigned char> vectorBuffer = (std::vector<unsigned char>)keto::asn1::SerializationHelper<Transaction>(transaction,&asn_DEF_Transaction);
    keto::asn1::DeserializationHelper<Transaction> deserializeHelper2(
            vectorBuffer,&asn_DEF_Transaction);
    Transaction* transaction3 = (Transaction*)deserializeHelper;
    xer_fprint(stdout, &asn_DEF_Transaction, transaction3);
    
    timeHelper2 = &transaction3->date;
    
    BOOST_CHECK( ((std::chrono::system_clock::time_point)timeHelper2).time_since_epoch().count() == 
            ((std::chrono::system_clock::time_point)timeHelper1).time_since_epoch().count() );
    
}