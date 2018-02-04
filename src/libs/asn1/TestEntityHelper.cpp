/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestEntityHelper.cpp
 * Author: ubuntu
 * 
 * Created on February 4, 2018, 7:51 AM
 */

#include "keto/asn1/TestEntityHelper.hpp"

namespace keto {
namespace asn1 {


TestEntityHelper::TestEntityHelper(const TestEntity& testEntity) : 
    testEntity(testEntity) {
}

TestEntityHelper::~TestEntityHelper() {
}

void* TestEntityHelper::getPtr() {
    return &testEntity;
}

struct asn_TYPE_descriptor_s* TestEntityHelper::getType() {
    return &asn_DEF_TestEntity;
}


}
}