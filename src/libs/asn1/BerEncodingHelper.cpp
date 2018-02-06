/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BerEncodingHelper.cpp
 * Author: Brett Chaldecott
 * 
 * Created on February 2, 2018, 4:03 AM
 */

#include <stdlib.h>

#include <botan/hex.h>
#include <botan/base64.h>

#include "keto/asn1/BerEncodingHelper.hpp"
#include "keto/asn1/Exception.hpp"

namespace keto {
namespace asn1 {
    
BerEncodingHelper::BerEncodingHelper() {
}

BerEncodingHelper::BerEncodingHelper(const keto::crypto::SecureVector& berEncoding) {
    this->berEncoding = berEncoding;
}

BerEncodingHelper::BerEncodingHelper(const BerEncoding_t& berEncoding) {
    copyHashToVector(berEncoding,this->berEncoding);
}


BerEncodingHelper::BerEncodingHelper(const std::string& berEncoding,keto::common::StringEncoding stringEncoding) {
    keto::crypto::SecureVector vector;
    if (stringEncoding == keto::common::HEX) {
        vector = Botan::hex_decode_locked(berEncoding,true);
    } else if (stringEncoding == keto::common::BASE64) {
        vector = Botan::base64_decode(berEncoding,true);
    } else {
        BOOST_THROW_EXCEPTION(keto::asn1::UnsupportedStringFormatException());
    }
    setValue(vector);
}


BerEncodingHelper::~BerEncodingHelper() {
}

BerEncodingHelper& BerEncodingHelper::operator=(const BerEncoding_t* berEncoding) {
    this->berEncoding.clear();
    copyHashToVector(*berEncoding,this->berEncoding);
    return (*this);
}


BerEncodingHelper& BerEncodingHelper::operator=(const BerEncoding_t& berEncoding) {
    this->berEncoding.clear();
    copyHashToVector(berEncoding,this->berEncoding);
    return (*this);
}

BerEncodingHelper::operator BerEncoding_t() const {
    BerEncoding_t* berEncodingT = (BerEncoding_t*)OCTET_STRING_new_fromBuf(&asn_DEF_BerEncoding,
            (const char *)this->berEncoding.data(),this->berEncoding.size());
    BerEncoding_t result = *berEncodingT;
    free(berEncodingT);
    return result;
}

BerEncodingHelper& BerEncodingHelper::operator =(const keto::crypto::SecureVector& berEncoding) {
    this->berEncoding = berEncoding;
    return (*this);
}


BerEncodingHelper::operator keto::crypto::SecureVector() const {
    return this->berEncoding;
}


BerEncodingHelper& BerEncodingHelper::setHash(const std::string& berEncoding,keto::common::StringEncoding stringEncoding) {
    keto::crypto::SecureVector vector;
    if (stringEncoding == keto::common::HEX) {
        vector = Botan::hex_decode_locked(berEncoding,true);
    } else if (stringEncoding == keto::common::BASE64) {
        vector = Botan::base64_decode(berEncoding,true);
    } else {
        BOOST_THROW_EXCEPTION(keto::asn1::UnsupportedStringFormatException());
    }
    setValue(vector);
    return (*this);
}


std::string BerEncodingHelper::getHash(keto::common::StringEncoding stringEncoding) {
    keto::crypto::SecureVector vector = getValue();
    if (stringEncoding == keto::common::HEX) {
        return Botan::hex_encode(vector,true);
    } else if (stringEncoding == keto::common::BASE64) {
        return Botan::base64_encode(vector);
    } else {
        BOOST_THROW_EXCEPTION(keto::asn1::UnsupportedStringFormatException());
    }
}


BerEncodingHelper& BerEncodingHelper::setValue(const keto::crypto::SecureVector& berEncoding) {
    BerEncoding_t* berEncodingT = (BerEncoding_t*)OCTET_STRING_new_fromBuf(&asn_DEF_BerEncoding,
            (const char *)this->berEncoding.data(),this->berEncoding.size());
    this->operator=(*berEncodingT);
    ASN_STRUCT_FREE(asn_DEF_BerEncoding,berEncodingT);
    return (*this);
}


keto::crypto::SecureVector BerEncodingHelper::getValue() {
    keto::crypto::SecureVector vector;
    copyHashToVector((BerEncoding_t)(*this),vector);
    return vector;
}

void BerEncodingHelper::copyHashToVector(const BerEncoding_t& berEncoding,keto::crypto::SecureVector& vector) {
    for (int index = 0; index < berEncoding.size; index++) {
        vector.push_back(berEncoding.buf[index]);
    }
}


}
}