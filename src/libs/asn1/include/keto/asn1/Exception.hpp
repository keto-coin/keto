/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Exception.hpp
 * Author: Brett Chaldecott
 *
 * Created on January 31, 2018, 4:37 PM
 */

#ifndef ASN1_EXCEPTION_HPP
#define ASN1_EXCEPTION_HPP

#include <string>
#include "keto/common/Exception.hpp"


namespace keto {
namespace asn1 {

// the keto environment exception base
KETO_DECLARE_EXCEPTION( ASN1Exception, "ASN1 Encoding failed." );

// the keto environment derived exception
KETO_DECLARE_DERIVED_EXCEPTION (ASN1Exception, SerializationException , "Failed to serialize.");
KETO_DECLARE_DERIVED_EXCEPTION (ASN1Exception, DeserializationException , "Failed to deserialize.");
KETO_DECLARE_DERIVED_EXCEPTION (ASN1Exception, IncompleteDataException , "Cannot deserialize as the data is incomplete.");

    
}
}

#endif /* EXCEPTION_HPP */

