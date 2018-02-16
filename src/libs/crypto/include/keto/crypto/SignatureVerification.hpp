/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SignatureVerification.hpp
 * Author: ubuntu
 *
 * Created on February 6, 2018, 12:07 PM
 */

#ifndef SIGNATUREVERIFICATION_HPP
#define SIGNATUREVERIFICATION_HPP

#include <vector>
#include <memory>

#include <botan/pk_keys.h>
#include <botan/pubkey.h>
#include <botan/x509_key.h>


#include "keto/crypto/Containers.hpp"

namespace keto {
namespace crypto {


class SignatureVerification {
public:
    SignatureVerification(std::shared_ptr<Botan::Public_Key> publicKey,
            const std::vector<uint8_t>& source);
    SignatureVerification(const std::vector<uint8_t>& key,
            keto::crypto::SecureVector source);
    SignatureVerification(const std::vector<uint8_t>& key,
            const std::vector<uint8_t>& source);
    SignatureVerification(const SignatureVerification& orig) = default;
    virtual ~SignatureVerification();
    
    bool check(const std::vector<uint8_t>& signature);
private:
    std::shared_ptr<Botan::Public_Key> publicKey;
    std::vector<uint8_t> key;
    std::vector<uint8_t> source;

};


}
}

#endif /* SIGNATUREVERIFICATION_HPP */

