/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SignatureHelper.cpp
 * Author: Brett Chaldecott
 * 
 * Created on February 2, 2018, 4:03 AM
 */

#include <stdlib.h>

#include <botan/hex.h>
#include <botan/base64.h>

#include "keto/asn1/SignatureHelper.hpp"
#include "keto/asn1/Exception.hpp"

namespace keto {
namespace asn1 {
    
SignatureHelper::SignatureHelper() {
}

SignatureHelper::SignatureHelper(const std::vector<uint8_t>& signature) {
    this->signature = signature;
}

SignatureHelper::SignatureHelper(const Signature_t& signature) {
    copyHashToVector(signature,this->signature);
}


SignatureHelper::SignatureHelper(const std::string& signature,keto::common::StringEncoding stringEncoding) {
    if (stringEncoding == keto::common::HEX) {
        this->signature = Botan::hex_decode(signature,true);
    } else if (stringEncoding == keto::common::BASE64) {
        copyFromSecureVector(Botan::base64_decode(signature,true), this->signature);
    } else {
        BOOST_THROW_EXCEPTION(keto::asn1::UnsupportedStringFormatException());
    }
}


SignatureHelper::~SignatureHelper() {
}

SignatureHelper& SignatureHelper::operator=(const Signature_t* signature) {
    this->signature.clear();
    copyHashToVector(*signature,this->signature);
    return (*this);
}


SignatureHelper& SignatureHelper::operator=(const Signature_t& signature) {
    this->signature.clear();
    copyHashToVector(signature,this->signature);
    return (*this);
}

SignatureHelper::operator Signature_t() const {
    Signature_t* signatureT = (Signature_t*)OCTET_STRING_new_fromBuf(&asn_DEF_Signature,
            (const char *)this->signature.data(),this->signature.size());
    Signature_t result = *signatureT;
    free(signatureT);
    return result;
}

SignatureHelper& SignatureHelper::operator =(const std::vector<uint8_t>& signature) {
    this->signature = signature;
    return (*this);
}


SignatureHelper::operator std::vector<uint8_t>() const {
    return this->signature;
}


SignatureHelper& SignatureHelper::setSignature(const std::string& signature,keto::common::StringEncoding stringEncoding) {
    if (stringEncoding == keto::common::HEX) {
        this->signature = Botan::hex_decode(signature,true);
    } else if (stringEncoding == keto::common::BASE64) {
        copyFromSecureVector(Botan::base64_decode(signature,true), this->signature);
    } else {
        BOOST_THROW_EXCEPTION(keto::asn1::UnsupportedStringFormatException());
    }
    return (*this);
}


std::string SignatureHelper::getSignature(keto::common::StringEncoding stringEncoding) {
    if (stringEncoding == keto::common::HEX) {
        return Botan::hex_encode(this->signature,true);
    } else if (stringEncoding == keto::common::BASE64) {
        return Botan::base64_encode(this->signature);
    } else {
        BOOST_THROW_EXCEPTION(keto::asn1::UnsupportedStringFormatException());
    }
}


void SignatureHelper::copyHashToVector(const Signature_t& signature,std::vector<uint8_t>& vector) {
    for (int index = 0; index < signature.size; index++) {
        vector.push_back(signature.buf[index]);
    }
}

void SignatureHelper::copyFromSecureVector(
    const keto::crypto::SecureVector& secureVector, std::vector<uint8_t>& vector) {
    keto::crypto::SecureVector localSecureVector(secureVector); 
    for (keto::crypto::SecureVector::iterator iter = localSecureVector.begin();
            iter != localSecureVector.end(); iter++) {
        vector.push_back(*iter);
    }
}

}
}