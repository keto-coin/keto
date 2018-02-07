/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HashGenerator.hpp
 * Author: ubuntu
 *
 * Created on February 6, 2018, 2:32 PM
 */

#ifndef HASHGENERATOR_HPP
#define HASHGENERATOR_HPP

#include <botan/hash.h>

#include "keto/crypto/Containers.hpp"

namespace keto {
namespace crypto {

class HashGenerator {
public:
    HashGenerator();
    HashGenerator(const HashGenerator& orig) = default;
    virtual ~HashGenerator();
    
    keto::crypto::SecureVector generateHash(const keto::crypto::SecureVector& bytes);
    keto::crypto::SecureVector generateHash(const std::vector<uint8_t>& bytes);
private:
    std::shared_ptr<Botan::HashFunction> hash256;
};


}
}
#endif /* HASHGENERATOR_HPP */

