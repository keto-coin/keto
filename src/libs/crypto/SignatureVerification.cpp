/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SignatureVerification.cpp
 * Author: ubuntu
 * 
 * Created on February 6, 2018, 12:07 PM
 */

#include <botan/pk_keys.h>
#include <botan/pubkey.h>
#include <botan/x509_key.h>

#include "keto/crypto/SignatureVerification.hpp"
#include "keto/crypto/Constants.hpp"


namespace keto {
namespace crypto {


SignatureVerification::SignatureVerification(const std::vector<uint8_t>& key, 
        keto::crypto::SecureVector source) : key(key) {
    for (keto::crypto::SecureVector::iterator iter = source.begin();
            iter != source.end(); iter++) {
        this->source.push_back(*iter);
    }
}

SignatureVerification::SignatureVerification(const std::vector<uint8_t>& key, 
        const std::vector<uint8_t>& source) : key(key), source(source) {
}

SignatureVerification::~SignatureVerification() {
}

bool SignatureVerification::check(const std::vector<uint8_t>& signature) {
    std::shared_ptr<Botan::Public_Key> publicKey(
             Botan::X509::load_key(key));
    Botan::PK_Verifier verify(*publicKey,Constants::SIGNATURE_TYPE);
    verify.update(this->source);
    return verify.check_signature(signature);
}


}
}