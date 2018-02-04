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

#include <botan/secmem.h>

#include "Hash.h"
#include "keto/common/StringCodec.hpp"

namespace keto {
namespace asn1 {

class HashHelper {
public:
    HashHelper();
    HashHelper(const Botan::secure_vector<uint8_t>& hash);
    HashHelper(const Hash_t& hash);
    HashHelper(const std::string& hash,keto::common::StringEncoding stringEncoding);
    
    HashHelper(const HashHelper& orig) = default;
    virtual ~HashHelper();
    
    HashHelper& operator=(const Hash_t* hash);
    HashHelper& operator=(const Hash_t& hash);
    operator Hash_t() const;
    
    HashHelper& operator =(const Botan::secure_vector<uint8_t>& hash);
    operator Botan::secure_vector<uint8_t>() const;
    
    HashHelper& setHash(const std::string& hash,keto::common::StringEncoding stringEncoding);
    std::string getHash(keto::common::StringEncoding stringEncoding);
    
    
private:
    Botan::secure_vector<uint8_t> hash;
    
    
    void copyHashToVector(const Hash_t& hash, Botan::secure_vector<uint8_t>& vector);
};


}
}


#endif /* HASHHELPER_HPP */

