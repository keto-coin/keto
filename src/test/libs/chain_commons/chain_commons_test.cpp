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



BOOST_AUTO_TEST_CASE( chain_commons_test ) {

    Number_t* value = (Number_t*)calloc(1,sizeof value);
    asn_long2INTEGER(value,100000000000000000);
    
    long lvalue;
    asn_INTEGER2long(value, &lvalue);
    
    std::cout << "The integer values is : " << lvalue << std::endl; 
}