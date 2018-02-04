/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AnyHelper.cpp
 * Author: ubuntu
 * 
 * Created on February 3, 2018, 11:15 AM
 */

#include "keto/asn1/AnyHelper.hpp"
#include "include/keto/asn1/AnyInterface.hpp"
#include <stdlib.h>

namespace keto {
namespace asn1 {

    
AnyHelper::AnyHelper(AnyInterface* anyInterface) : 
    anyInterface(anyInterface)  {
    this->any = 0;
    
}

AnyHelper::AnyHelper(ANY_t* any) : 
    any(any)  {
    this->anyInterface = 0;
}

AnyHelper::~AnyHelper() {
}

AnyHelper::operator ANY_t() {
    if (any) {
        return *any;
    }
    ANY_t* ptr = (ANY_t*)calloc(1, sizeof ptr);
    if (!anyInterface) {
        BOOST_THROW_EXCEPTION(keto::asn1::NoAnyTypeInfoFailedException());
    }
    if (ANY_fromType(ptr, anyInterface->getType(), anyInterface->getPtr()) == -1) {
        free(ptr);
        BOOST_THROW_EXCEPTION(keto::asn1::TypeToAnyConversionFailedException());
    }
    ANY_t result = (*ptr);
    free(ptr);
    return result;
}

}
}