/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SecureVectorUtils.cpp
 * Author: ubuntu
 * 
 * Created on February 16, 2018, 11:42 AM
 */

#include "keto/crypto/SecureVectorUtils.hpp"

namespace keto {
namespace crypto {

SecureVectorUtils::SecureVectorUtils() {
}

SecureVectorUtils::~SecureVectorUtils() {
}

std::vector<uint8_t> SecureVectorUtils::copyFromSecure(const SecureVector& secureVector) {
    SecureVector copySecureVector = secureVector;
    return copyFromSecure(copySecureVector);
}

std::vector<uint8_t> SecureVectorUtils::copyFromSecure(SecureVector& secureVector) {
    std::vector<uint8_t> result;
    for (SecureVector::iterator iter = secureVector.begin();
            iter != secureVector.end(); iter++) {
        result.push_back(*iter);
    }
    return result;
}

SecureVector SecureVectorUtils::copyToSecure(const std::vector<uint8_t>& vector) {
    std::vector<uint8_t> vectorCopy = vector;
    return copyToSecure(vectorCopy);
}

SecureVector SecureVectorUtils::copyToSecure(std::vector<uint8_t>& vector) {
    SecureVector result;
    for (std::vector<uint8_t>::iterator iter = vector.begin();
            iter != vector.end(); iter++) {
        result.push_back(*iter);
    }
    return result;
}


}
}
