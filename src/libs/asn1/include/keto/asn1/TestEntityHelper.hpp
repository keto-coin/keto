/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestEntityHelper.hpp
 * Author: ubuntu
 *
 * Created on February 4, 2018, 7:51 AM
 */

#ifndef TESTENTITYHELPER_HPP
#define TESTENTITYHELPER_HPP

#include "TestEntity.h"
#include "keto/asn1/AnyInterface.hpp"

namespace keto {
namespace asn1 {


class TestEntityHelper : virtual public AnyInterface {
public:
    TestEntityHelper(const TestEntity& testEntity);
    TestEntityHelper(const TestEntityHelper& orig) = default;
    virtual ~TestEntityHelper();
    
    virtual void* getPtr();
    virtual struct asn_TYPE_descriptor_s* getType();
    
private:
    TestEntity testEntity;
};


}
}

#endif /* TESTENTITYHELPER_HPP */

