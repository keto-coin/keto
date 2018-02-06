/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SignatureHelper.hpp
 * Author: ubuntu
 *
 * Created on February 2, 2018, 4:03 AM
 */

#ifndef SIGNATURE_HELPER_HPP
#define SIGNATURE_HELPER_HPP

#include <string>

#include "Signature.h"
#include "keto/common/StringCodec.hpp"
#include "keto/crypto/Containers.hpp"

namespace keto {
namespace asn1 {

class SignatureHelper {
public:
    SignatureHelper();
    SignatureHelper(const std::vector<uint8_t>& signature);
    SignatureHelper(const Signature_t& signature);
    SignatureHelper(const std::string& signature,keto::common::StringEncoding stringEncoding);
    
    SignatureHelper(const SignatureHelper& orig) = default;
    virtual ~SignatureHelper();
    
    SignatureHelper& operator=(const Signature_t* signature);
    SignatureHelper& operator=(const Signature_t& signature);
    operator Signature_t() const;
    
    SignatureHelper& operator =(const std::vector<uint8_t>& signature);
    operator std::vector<uint8_t>() const;
    
    SignatureHelper& setSignature(const std::string& signature,keto::common::StringEncoding stringEncoding);
    std::string getSignature(keto::common::StringEncoding stringEncoding);
    
    
private:
    std::vector<uint8_t> signature;
    
    
    void copyHashToVector(const Signature_t& signature, std::vector<uint8_t>& vector);
    void copyFromSecureVector(const keto::crypto::SecureVector& secureVector, std::vector<uint8_t>& vector);
};


}
}


#endif /* HASHHELPER_HPP */

