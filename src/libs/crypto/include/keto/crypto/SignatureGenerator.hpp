/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SignatureGenerator.hpp
 * Author: ubuntu
 *
 * Created on February 6, 2018, 11:27 AM
 */

#ifndef SIGNATURE_GENERATOR_HPP
#define SIGNATURE_GENERATOR_HPP

#include "keto/crypto/Constants.hpp"
#include "keto/crypto/Containers.hpp"

namespace keto {
namespace crypto {


class SignatureGenerator {
public:
    SignatureGenerator(const keto::crypto::SecureVector& key);
    SignatureGenerator(const SignatureGenerator& orig) = default;
    virtual ~SignatureGenerator();
    
    std::vector<uint8_t> sign(std::vector<uint8_t>& value);
    std::vector<uint8_t> sign(const keto::crypto::SecureVector& value);
    
private:
    keto::crypto::SecureVector key;
    
};


}
}
#endif /* SIGNATURETOOL_HPP */

