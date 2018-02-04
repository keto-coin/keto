/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HashHelper.hpp
 * Author: ubuntu
 *
 * Created on February 2, 2018, 4:03 AM
 */

#ifndef HASHHELPER_HPP
#define HASHHELPER_HPP

#include <string>

#include "Hash.h"
#include "keto/common/StringCodec.hpp"
#include "keto/crypto/Containers.hpp"

namespace keto {
namespace asn1 {

class HashHelper {
public:
    HashHelper();
    HashHelper(const keto::crypto::SecureVector& hash);
    HashHelper(const Hash_t& hash);
    HashHelper(const std::string& hash,keto::common::StringEncoding stringEncoding);
    
    HashHelper(const HashHelper& orig) = default;
    virtual ~HashHelper();
    
    HashHelper& operator=(const Hash_t* hash);
    HashHelper& operator=(const Hash_t& hash);
    operator Hash_t() const;
    
    HashHelper& operator =(const keto::crypto::SecureVector& hash);
    operator keto::crypto::SecureVector() const;
    
    HashHelper& setHash(const std::string& hash,keto::common::StringEncoding stringEncoding);
    std::string getHash(keto::common::StringEncoding stringEncoding);
    
    
private:
    keto::crypto::SecureVector hash;
    
    
    void copyHashToVector(const Hash_t& hash, keto::crypto::SecureVector& vector);
};


}
}


#endif /* HASHHELPER_HPP */

