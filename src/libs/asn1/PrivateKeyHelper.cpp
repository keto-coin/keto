/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PrivateKeyHelper.cpp
 * Author: Brett Chaldecott
 * 
 * Created on February 2, 2018, 4:03 AM
 */

#include <stdlib.h>

#include <botan/hex.h>
#include <botan/base64.h>

#include "keto/asn1/PrivateKeyHelper.hpp"
#include "keto/asn1/SerializationHelper.hpp"
#include "keto/asn1/DeserializationHelper.hpp"
#include "keto/asn1/Exception.hpp"
#include "keto/common/MetaInfo.hpp"

namespace keto {
namespace asn1 {
    
PrivateKeyHelper::PrivateKeyHelper() {
    initPrivateKey();
}

PrivateKeyHelper::PrivateKeyHelper(const keto::crypto::SecureVector& privateKey) {
    keto::asn1::DeserializationHelper<PrivateKey> deserializeHelper(
            privateKey,&asn_DEF_PrivateKey);
    this->privateKey = deserializeHelper.takePtr();
}

PrivateKeyHelper::PrivateKeyHelper(const PrivateKey_t& privateKey) {
    initPrivateKey();
    // duplicate the private key
    this->privateKey->key = BerEncodingHelper(privateKey.key);
}

PrivateKeyHelper::PrivateKeyHelper(const PrivateKeyHelper& privateKeyHelper) {
    initPrivateKey();
    // duplicate the private key
    this->privateKey->key = BerEncodingHelper(privateKeyHelper.privateKey->key);
}

PrivateKeyHelper::~PrivateKeyHelper() {
    this->freePrivateKey();
}

PrivateKeyHelper& PrivateKeyHelper::setKey(const BerEncodingHelper& key) {
    this->privateKey->key = key;
    return (*this);
}

BerEncodingHelper PrivateKeyHelper::getKey() {
    return this->privateKey->key;
}


PrivateKeyHelper& PrivateKeyHelper::operator=(const PrivateKey_t* privateKey) {
    this->freePrivateKey();
    initPrivateKey();
    this->privateKey->key = BerEncodingHelper(privateKey->key);
    return (*this);
}


PrivateKeyHelper& PrivateKeyHelper::operator=(const PrivateKey_t& privateKey) {
    this->freePrivateKey();
    initPrivateKey();
    this->privateKey->key = BerEncodingHelper(privateKey.key);
    return (*this);
}

PrivateKeyHelper::operator PrivateKey_t() const {
    PrivateKey_t result;
    result.version = this->privateKey->version;
    result.key = BerEncodingHelper(this->privateKey->key);
    return result;
}

PrivateKeyHelper& PrivateKeyHelper::operator =(const keto::crypto::SecureVector& privateKey) {
    this->freePrivateKey();
    keto::asn1::DeserializationHelper<PrivateKey> deserializeHelper(
            privateKey,&asn_DEF_PrivateKey);
    this->privateKey = deserializeHelper.takePtr();
    return (*this);
}


PrivateKeyHelper::operator keto::crypto::SecureVector() {
    serializePrivateKey();
    return this->serializationHelperPtr->operator keto::crypto::SecureVector();
}


void PrivateKeyHelper::initPrivateKey() {
    this->privateKey = (PrivateKey_t*)calloc(1,sizeof *this->privateKey);
    this->privateKey->version = keto::common::MetaInfo::PROTOCOL_VERSION;
}


void PrivateKeyHelper::freePrivateKey() {
    if (this->privateKey) {
        ASN_STRUCT_FREE(asn_DEF_PrivateKey,this->privateKey);
        this->privateKey = 0;
    }
}

void PrivateKeyHelper::serializePrivateKey() {
    this->serializationHelperPtr = 
            std::make_shared<keto::asn1::SerializationHelper<PrivateKey>>(
            this->privateKey,&asn_DEF_PrivateKey);
}

}
}