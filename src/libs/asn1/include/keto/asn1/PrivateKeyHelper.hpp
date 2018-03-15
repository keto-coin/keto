/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PrivateKeyHelper.hpp
 * Author: ubuntu
 *
 * Created on February 2, 2018, 4:03 AM
 */

#ifndef PRIVATE_KEY_HELPER_HPP
#define PRIVATE_KEY_HELPER_HPP

#include <string>

#include "PrivateKey.h"
#include "keto/common/StringCodec.hpp"
#include "keto/crypto/Containers.hpp"
#include "keto/asn1/BerEncodingHelper.hpp"
#include "keto/asn1/SerializationHelper.hpp"


namespace keto {
namespace asn1 {

class PrivateKeyHelper {
public:
    PrivateKeyHelper();
    PrivateKeyHelper(const keto::crypto::SecureVector& privateKey);
    PrivateKeyHelper(const PrivateKey_t& privateKey);
    PrivateKeyHelper(const std::string& orig,keto::common::StringEncoding stringEncoding);
    PrivateKeyHelper(const PrivateKeyHelper& orig);
    virtual ~PrivateKeyHelper();
    
    PrivateKeyHelper& setKey(const BerEncodingHelper& key);
    BerEncodingHelper getKey();
    
    PrivateKeyHelper& operator=(const PrivateKey_t* privateKey);
    PrivateKeyHelper& operator=(const PrivateKey_t& privateKey);
    operator PrivateKey_t() const;
    
    PrivateKeyHelper& operator =(const keto::crypto::SecureVector& privateKey);
    operator keto::crypto::SecureVector();
    
private:
    PrivateKey_t* privateKey;
    std::shared_ptr<keto::asn1::SerializationHelper<PrivateKey>> serializationHelperPtr;
    
    void initPrivateKey();
    void freePrivateKey();
    void serializePrivateKey();
};


}
}


#endif /* HASHHELPER_HPP */

