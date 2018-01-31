/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#define BOOST_TEST_MODULE AsnTest
#include <boost/test/unit_test.hpp>
#include <iostream>
#include "keto/asn1/TimeHelper.hpp"

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
}