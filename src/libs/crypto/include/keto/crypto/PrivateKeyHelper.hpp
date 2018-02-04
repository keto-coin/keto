/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PrivateKeyHelper.hpp
 * Author: Brett Chaldecott
 *
 * Created on February 4, 2018, 1:38 PM
 */

#ifndef PRIVATEKEYHELPER_HPP
#define PRIVATEKEYHELPER_HPP

#include <string>


#include "keto/crypto/Containers.hpp"


namespace keto {
namespace crypto {

class PrivateKeyHelper {
public:
    PrivateKeyHelper();
    PrivateKeyHelper(const SecureVector& privateKey);
    PrivateKeyHelper(const uint8_t* privateKey, const size_t size);
    PrivateKeyHelper(const PrivateKeyHelper& orig) = default;
    virtual ~PrivateKeyHelper();
    
    PrivateKeyHelper& operator=(const SecureVector& privateKey);
    PrivateKeyHelper& setKey(const uint8_t* privateKey, const size_t size);
    
    operator uint8_t*();
    operator SecureVector();
    
    size_t size();
    
private:
    SecureVector privateKey;
    
    void copyKey(const uint8_t* privateKey, const size_t size);
};


}
}

#endif /* PRIVATEKEYHELPER_HPP */

