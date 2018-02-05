/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   KeyHelper.cpp
 * Author: Brett Chaldecott
 * 
 * Created on February 2, 2018, 4:03 AM
 */

#include <stdlib.h>

#include <botan/hex.h>
#include <botan/base64.h>

#include "keto/asn1/KeyHelper.hpp"
#include "keto/asn1/Exception.hpp"

namespace keto {
namespace asn1 {
    
KeyHelper::KeyHelper() {
}

KeyHelper::KeyHelper(const keto::crypto::SecureVector& key) {
    this->key = key;
}

KeyHelper::KeyHelper(const Key_t& key) {
    copyHashToVector(key,this->key);
}


KeyHelper::KeyHelper(const std::string& key,keto::common::StringEncoding stringEncoding) {
    if (stringEncoding == keto::common::HEX) {
        this->key = Botan::hex_decode_locked(key,true);
    } else if (stringEncoding == keto::common::BASE64) {
        this->key = Botan::base64_decode(key,true);
    } else {
        BOOST_THROW_EXCEPTION(keto::asn1::UnsupportedStringFormatException());
    }
}


KeyHelper::~KeyHelper() {
}

KeyHelper& KeyHelper::operator=(const Key_t* key) {
    this->key.clear();
    copyHashToVector(*key,this->key);
    return (*this);
}


KeyHelper& KeyHelper::operator=(const Key_t& key) {
    this->key.clear();
    copyHashToVector(key,this->key);
    return (*this);
}

KeyHelper::operator Key_t() const {
    Key_t* keyT = (Key_t*)OCTET_STRING_new_fromBuf(&asn_DEF_Key,
            (const char *)this->key.data(),this->key.size());
    Key_t result = *keyT;
    free(keyT);
    return result;
}

KeyHelper& KeyHelper::operator =(const keto::crypto::SecureVector& key) {
    this->key = key;
    return (*this);
}


KeyHelper::operator keto::crypto::SecureVector() const {
    return this->key;
}


KeyHelper& KeyHelper::setHash(const std::string& key,keto::common::StringEncoding stringEncoding) {
    if (stringEncoding == keto::common::HEX) {
        this->key = Botan::hex_decode_locked(key,true);
    } else if (stringEncoding == keto::common::BASE64) {
        this->key = Botan::base64_decode(key,true);
    } else {
        BOOST_THROW_EXCEPTION(keto::asn1::UnsupportedStringFormatException());
    }
    return (*this);
}


std::string KeyHelper::getHash(keto::common::StringEncoding stringEncoding) {
    if (stringEncoding == keto::common::HEX) {
        return Botan::hex_encode(this->key,true);
    } else if (stringEncoding == keto::common::BASE64) {
        return Botan::base64_encode(this->key);
    } else {
        BOOST_THROW_EXCEPTION(keto::asn1::UnsupportedStringFormatException());
    }
}


void KeyHelper::copyHashToVector(const Key_t& key,keto::crypto::SecureVector& vector) {
    for (int index = 0; index < key.size; index++) {
        vector.push_back(key.buf[index]);
    }
}


}
}