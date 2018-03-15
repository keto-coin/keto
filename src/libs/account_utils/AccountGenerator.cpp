/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AccountGenerator.cpp
 * Author: ubuntu
 * 
 * Created on March 8, 2018, 6:14 PM
 */

#include <iostream>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <nlohmann/json.hpp>
#include <botan/hex.h>

#include "keto/account_utils/AccountGenerator.hpp"
#include "keto/account_utils/Exceptions.hpp"
#include "include/keto/account_utils/AccountGenerator.hpp"

namespace keto {
namespace account_utils {


AccountGenerator::AccountGenerator() : generator(new Botan::AutoSeeded_RNG()) {
    std::cout << "Generate a new key " << std::endl;
    this->privateKey = std::shared_ptr<Botan::Private_Key>(
            new Botan::RSA_PrivateKey(*generator, 2056));
    Botan::RSA_PrivateKey* privateKey = (Botan::RSA_PrivateKey*)this->privateKey.get();
    this->publicKey = std::shared_ptr<Botan::Public_Key>(
            new Botan::RSA_PublicKey(*privateKey));
}

AccountGenerator::AccountGenerator(const std::string& privateKeyPath) : generator(new Botan::AutoSeeded_RNG()){
        // setup the paths using the environmental variables
    boost::filesystem::path keyPath = privateKeyPath;
    std::cout << "Key path is : " << keyPath.string() << std::endl;
    if (!boost::filesystem::exists(keyPath)) {
        BOOST_THROW_EXCEPTION(keto::account_utils::InvalidPrivateKeyPathException());
    }
    this->privateKey = std::shared_ptr<Botan::Private_Key>(
            Botan::PKCS8::load_key(keyPath.string(), *generator));
    Botan::RSA_PrivateKey* privateKey = (Botan::RSA_PrivateKey*)this->privateKey.get();
    this->publicKey = std::shared_ptr<Botan::Public_Key>(
            new Botan::RSA_PublicKey(*privateKey));
}
    

AccountGenerator::~AccountGenerator() {
}

keto::crypto::SecureVector AccountGenerator::getAccountHash() {
    std::unique_ptr<Botan::HashFunction> hash256(Botan::HashFunction::create("SHA-256"));
    return hash256->process(this->privateKey->private_key_bits());
}

keto::crypto::SecureVector AccountGenerator::getPrivateKey() {
    return Botan::PKCS8::BER_encode(*this->privateKey);
}

std::vector<uint8_t> AccountGenerator::getPublicKey() {
    return this->publicKey->public_key_bits();
}

AccountGenerator::operator std::string() {
    nlohmann::json json = {
        {"account_hash", Botan::hex_encode(getAccountHash(),true)},
        {"public_key", Botan::hex_encode(getPublicKey(),true)},
        {"private_key", Botan::hex_encode(getPrivateKey(),true)}
      };
    return json.dump();
}


}
}