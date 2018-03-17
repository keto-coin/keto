/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#define BOOST_TEST_MODULE AsnTest
#include <boost/test/unit_test.hpp>
#include <iostream>
#include "TestEntity.h"
#include "keto/common/MetaInfo.hpp"
#include "keto/asn1/TimeHelper.hpp"
#include "keto/asn1/NumberHelper.hpp"
#include "keto/asn1/HashHelper.hpp"
#include "keto/asn1/SerializationHelper.hpp"
#include "keto/asn1/DeserializationHelper.hpp"
#include "keto/asn1/TestEntityHelper.hpp"
#include "keto/asn1/AnyHelper.hpp"



BOOST_AUTO_TEST_CASE( asn1_test ) {
    // test the time helper
    keto::asn1::TimeHelper timeHelper1;
    keto::asn1::TimeHelper timeHelper2;
    
    // this performs a slice
    timeHelper2 = (UTCTime_t)timeHelper1;
    timeHelper1 = (UTCTime_t)timeHelper2;
    
    std::cout << "The duration is : " << ((std::chrono::system_clock::time_point)timeHelper2).time_since_epoch().count() << std::endl;
    std::cout << "The duration is : " << ((std::chrono::system_clock::time_point)timeHelper1).time_since_epoch().count() << std::endl;
    
    BOOST_CHECK( ((std::chrono::system_clock::time_point)timeHelper2).time_since_epoch().count() == 
            ((std::chrono::system_clock::time_point)timeHelper1).time_since_epoch().count() );
    
    
    // instanciate a transaction
    TestEntity* testEntity = 0;
    testEntity = (TestEntity*)calloc(1, sizeof *testEntity);
    testEntity->version = keto::common::MetaInfo::PROTOCOL_VERSION;
    testEntity->date = (UTCTime_t)keto::asn1::TimeHelper();
    
    std::cout << "The pre serialized state is " << std::endl;
    xer_fprint(stdout, &asn_DEF_TestEntity, testEntity);
    std::cout << std::endl;
    
    keto::asn1::SerializationHelper<TestEntity> serializationHelper(testEntity,&asn_DEF_TestEntity);
    uint8_t* buffer = (uint8_t*)serializationHelper;
    keto::asn1::DeserializationHelper<TestEntity> deserializeHelper(
            buffer,serializationHelper.size(),&asn_DEF_TestEntity);
    TestEntity* testEntity2 = (TestEntity*)deserializeHelper;
    std::cout << "The deserialized state is " << std::endl;
    xer_fprint(stdout, &asn_DEF_TestEntity, testEntity2);
    std::cout << std::endl;
    
    timeHelper1 = testEntity->date;
    timeHelper2 = testEntity2->date;
    
    BOOST_CHECK( ((std::chrono::system_clock::time_point)timeHelper2).time_since_epoch().count() == 
            ((std::chrono::system_clock::time_point)timeHelper1).time_since_epoch().count() );
    
    free(buffer);
    
    keto::asn1::SerializationHelper<TestEntity> serializationHelper2(testEntity,&asn_DEF_TestEntity);
    
    std::vector<uint8_t> vectorBuffer2 = (std::vector<uint8_t>)serializationHelper2;
    keto::asn1::DeserializationHelper<TestEntity> deserializeHelper3(
            vectorBuffer2,&asn_DEF_TestEntity);
    TestEntity* testEntity4 = (TestEntity*)deserializeHelper3;
    std::cout << "The deserialized state is " << std::endl;
    xer_fprint(stdout, &asn_DEF_TestEntity, testEntity4);
    std::cout << std::endl;
    
    
    keto::asn1::DeserializationHelper<TestEntity> deserializeHelper2(
            (std::vector<uint8_t>)keto::asn1::SerializationHelper<TestEntity>(testEntity,&asn_DEF_TestEntity),
            &asn_DEF_TestEntity);
    //uint8_t* buffer2 = (uint8_t*)serializationHelper;
    //keto::asn1::DeserializationHelper<TestEntity> deserializeHelper2(
    //        buffer2,serializationHelper.size(),&asn_DEF_TestEntity);
    
    TestEntity* testEntity3 = (TestEntity*)deserializeHelper2;
    std::cout << "The deserialized state is " << std::endl;
    xer_fprint(stdout, &asn_DEF_TestEntity, testEntity3);
    std::cout << std::endl;
    
    timeHelper2 = testEntity3->date;
    
    BOOST_CHECK( ((std::chrono::system_clock::time_point)timeHelper2).time_since_epoch().count() == 
            ((std::chrono::system_clock::time_point)timeHelper1).time_since_epoch().count() );
    
    long value = 10;
    Number_t number = (Number_t)keto::asn1::NumberHelper(value);
    long value2 = (long)keto::asn1::NumberHelper(number);
    std::cout << "Value 1: " << value << " Value 2 : " << value2 << std::endl;
    BOOST_CHECK(value == value2);
    
    keto::asn1::NumberHelper numberHelper(10);
    Number_t number2 = (Number_t)numberHelper = numberHelper + 20;
    numberHelper += number2;
    number2 = (Number_t)numberHelper;
    long value3 = (long)keto::asn1::NumberHelper(number2);
    std::cout << "Value 3: " << value3 << std::endl;
    
    
    keto::asn1::HashHelper 
        hashHelper(
        "3D89018355E055923478E8E816D82A26A8AA10A2AE5B497847084AB7F54B9238",
        keto::common::HEX);
    Hash_t hash_t = (Hash_t)hashHelper;
    keto::asn1::HashHelper hashHelper2(hash_t);
    std::cout << "Hash value : " << hashHelper.getHash(keto::common::HEX) << std::endl;
    std::cout << "Hash value : " << hashHelper2.getHash(keto::common::HEX) << std::endl;
    BOOST_CHECK(0 == hashHelper.getHash(keto::common::HEX).compare(
            hashHelper2.getHash(keto::common::HEX)));
    
    
    keto::asn1::TestEntityHelper testEntityHelper(*testEntity);
    keto::asn1::AnyHelper anyHelper(&testEntityHelper);
    ANY_t any = (ANY_t)anyHelper;
    
    keto::asn1::AnyHelper anyHelper2(any);
    TestEntity* testEntity5 = (TestEntity*)anyHelper2.extract<TestEntity>(&asn_DEF_TestEntity);
    
    keto::asn1::TimeHelper timeHelper3 = testEntity5->date;
    
    BOOST_CHECK( ((std::chrono::system_clock::time_point)timeHelper3).time_since_epoch().count() == 
            ((std::chrono::system_clock::time_point)timeHelper1).time_since_epoch().count() );
    xer_fprint(stdout, &asn_DEF_TestEntity, testEntity5);
    
}