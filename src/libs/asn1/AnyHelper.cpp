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

#include "AnyHelper.hpp"
#include "include/keto/asn1/AnyInterface.hpp"
#include <stdlib.h>

namespace keto {
namespace asn1 {

    
AnyHelper::AnyHelper(const AnyInterface* anyInterface) : 
    anyInterface(anyInterface), any(0)  {
    
}

AnyHelper::AnyHelper(const ANY_t* any) : 
    anyInterface(0), any(any)  {
    
}

AnyHelper::~AnyHelper() {
}

AnyHelper::operator ANY_t() {
    ANY_t* ptr = (ANY)calloc(1, sizeof result);
    if (!anyInterface) {
        BOOST_THROW_EXCEPTION(keto::asn1::NoAnyTypeInfoFailedException());
    }
    if (ANY_fromType(ptr, anyInterface->getType(), anyInterface->getPtr()) == -1) {
        free(result);
        BOOST_THROW_EXCEPTION(keto::asn1::TypeToAnyConversionFailedException());
    }
    ANY_t result = (*ptr);
    free(ptr);
    return result;
}

}
}