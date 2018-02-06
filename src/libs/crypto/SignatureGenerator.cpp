/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SignatureGenerator.cpp
 * Author: brett chaldecott
 * 
 * Created on February 6, 2018, 11:27 AM
 */

#include <botan/pkcs8.h>
#include <botan/hash.h>
#include <botan/data_src.h>
#include <botan/pubkey.h>
#include <botan/rng.h>
#include <botan/auto_rng.h>


#include "keto/crypto/SignatureGenerator.hpp"
#include "keto/crypto/Constants.hpp"

namespace keto {
namespace crypto {


SignatureGenerator::SignatureGenerator(const keto::crypto::SecureVector& key) : 
    key(key){
}

SignatureGenerator::~SignatureGenerator() {
}


std::vector<uint8_t> SignatureGenerator::sign(std::vector<uint8_t>& value) {
    Botan::DataSource_Memory memoryDatasource(key);
    std::unique_ptr< Botan::Private_Key > privateKey = 
            Botan::PKCS8::load_key(memoryDatasource);
    // present 
    std::unique_ptr<Botan::RandomNumberGenerator> rng(new Botan::AutoSeeded_RNG);
    Botan::PK_Signer signer(*privateKey, *rng, Constants::SIGNATURE_TYPE);
    return signer.sign_message(value, *rng);
}


std::vector<uint8_t> SignatureGenerator::sign(const keto::crypto::SecureVector& value) {
    Botan::DataSource_Memory memoryDatasource(key);
    std::unique_ptr< Botan::Private_Key > privateKey = 
            Botan::PKCS8::load_key(memoryDatasource);
    // present 
    std::unique_ptr<Botan::RandomNumberGenerator> rng(new Botan::AutoSeeded_RNG);
    Botan::PK_Signer signer(*privateKey, *rng, Constants::SIGNATURE_TYPE);
    return signer.sign_message(value, *rng);
}

}
}