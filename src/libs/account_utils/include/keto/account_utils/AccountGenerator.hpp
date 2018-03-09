/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AccountGenerator.hpp
 * Author: ubuntu
 *
 * Created on March 8, 2018, 6:14 PM
 */

#ifndef ACCOUNTGENERATOR_HPP
#define ACCOUNTGENERATOR_HPP

#include <string>
#include <vector>

#include <botan/pkcs8.h>
#include <botan/rsa.h>
#include <botan/hash.h>
#include <botan/data_src.h>
#include <botan/pubkey.h>
#include <botan/rng.h>
#include <botan/auto_rng.h>

#include "keto/crypto/Containers.hpp"


namespace keto {
namespace account_utils {
        
class AccountGenerator {
public:
    AccountGenerator();
    AccountGenerator(const std::string& privateKeyPath);
    AccountGenerator(const AccountGenerator& orig) = default;
    virtual ~AccountGenerator();
    
    keto::crypto::SecureVector getAccountHash();
    keto::crypto::SecureVector getPrivateKey();
    std::vector<uint8_t> getPublicKey();
    
    operator std::string();
private:
    std::shared_ptr<Botan::AutoSeeded_RNG> generator;
    std::shared_ptr<Botan::Private_Key> privateKey;
    std::shared_ptr<Botan::Public_Key> publicKey;
};


}
}


#endif /* ACCOUNTGENERATOR_HPP */

