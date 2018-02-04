/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   KeyHelper.hpp
 * Author: ubuntu
 *
 * Created on February 2, 2018, 4:03 AM
 */

#ifndef KEYHELPER_HPP
#define KEYHELPER_HPP

#include <string>

#include "Key.h"
#include "keto/common/StringCodec.hpp"
#include "keto/crypto/Containers.hpp"

namespace keto {
namespace asn1 {

class KeyHelper {
public:
    KeyHelper();
    KeyHelper(const keto::crypto::SecureVector& key);
    KeyHelper(const Key_t& key);
    KeyHelper(const std::string& key,keto::common::StringEncoding stringEncoding);
    
    KeyHelper(const KeyHelper& orig) = default;
    virtual ~KeyHelper();
    
    KeyHelper& operator=(const Key_t* key);
    KeyHelper& operator=(const Key_t& key);
    operator Key_t() const;
    
    KeyHelper& operator =(const keto::crypto::SecureVector& key);
    operator keto::crypto::SecureVector() const;
    
    KeyHelper& setHash(const std::string& key,keto::common::StringEncoding stringEncoding);
    std::string getHash(keto::common::StringEncoding stringEncoding);
    
    
private:
    keto::crypto::SecureVector key;
    
    
    void copyHashToVector(const Key_t& key, keto::crypto::SecureVector& vector);
};


}
}


#endif /* HASHHELPER_HPP */

