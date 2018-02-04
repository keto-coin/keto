/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PrivateKeyHelper.cpp
 * Author: ubuntu
 * 
 * Created on February 4, 2018, 1:38 PM
 */

#include "keto/crypto/PrivateKeyHelper.hpp"

namespace keto {
namespace crypto {


PrivateKeyHelper::PrivateKeyHelper() {
}

PrivateKeyHelper::PrivateKeyHelper(const SecureVector& privateKey) : 
    privateKey(privateKey) {
}


PrivateKeyHelper::PrivateKeyHelper(const uint8_t* privateKey, const size_t size) {
    this->copyKey(privateKey,size);
}


PrivateKeyHelper::~PrivateKeyHelper() {
}


PrivateKeyHelper& PrivateKeyHelper::operator=(const SecureVector& privateKey) {
    this->privateKey = privateKey;
    return (*this);
}


PrivateKeyHelper& PrivateKeyHelper::setKey(const uint8_t* privateKey, const size_t size) {
    this->copyKey(privateKey,size);
}

PrivateKeyHelper::operator uint8_t*() {
    uint8_t* key = (uint8_t*)malloc(this->privateKey.size());
    for (int index = 0; index < this->privateKey.size(); index++) {
        key[index] = this->privateKey[index];
    }
    return key;
}


PrivateKeyHelper::operator SecureVector() {
    return this->privateKey;
}

size_t PrivateKeyHelper::size() {
    return this->privateKey.size();
}

void PrivateKeyHelper::copyKey(const uint8_t* privateKey, const size_t size) {
    this->privateKey.clear();
    for (int index = 0; index < size; index++) {
        this->privateKey.push_back(privateKey[index]);
    }
}

}
}