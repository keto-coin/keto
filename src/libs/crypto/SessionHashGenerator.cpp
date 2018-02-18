/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SessionHashGenerator.cpp
 * Author: ubuntu
 * 
 * Created on February 16, 2018, 6:59 AM
 */

#include <vector>
#include <chrono>
#include <cstdlib>
#include <time.h>

#include "keto/crypto/SessionHashGenerator.hpp"
#include "keto/crypto/HashGenerator.hpp"
#include "keto/crypto/SecureVectorUtils.hpp"
#include "include/keto/crypto/SecureVectorUtils.hpp"
#include "include/keto/crypto/SessionHashGenerator.hpp"

namespace keto {
namespace crypto {


SessionHashGenerator::SessionHashGenerator(const std::vector<uint8_t>& clientHash,
            const std::vector<uint8_t>& accountHash) {
    auto duration = std::chrono::system_clock::now().time_since_epoch();
    unsigned long microsecondsLong = 
        std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
    uint8_t* longPointer = (uint8_t*)&microsecondsLong;
    
    // setup srand and get a random integer
    unsigned int seedp = time(0);
    int randomNumber = rand_r(&seedp);
    uint8_t* randomNumberPointer = (uint8_t*)&randomNumber;
    
    // copy values to byte vector
    std::vector<uint8_t> byteVector;
    
    byteVector.insert(byteVector.end(),clientHash.begin(),clientHash.end());
    byteVector.insert(byteVector.end(),accountHash.begin(),accountHash.end());
    
    // copy the time stamp in microseconds
    for (int index = 0; index < sizeof(microsecondsLong); index++) {
        byteVector.push_back(longPointer[index]);
    }
    
    // copy the random number
    for (int index = 0; index < sizeof(randomNumber); index++) {
        byteVector.push_back(randomNumberPointer[index]);
    }
    
    keto::crypto::SecureVector secureVector = 
            HashGenerator().generateHash(byteVector);
    
    this->bytes = SecureVectorUtils().copyFromSecure(secureVector);
    
}

SessionHashGenerator::~SessionHashGenerator() {
}


std::vector<uint8_t> SessionHashGenerator::getHash() {
    return this->bytes;
}

}
}