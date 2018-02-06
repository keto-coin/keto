/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BerEncodingHelper.hpp
 * Author: ubuntu
 *
 * Created on February 2, 2018, 4:03 AM
 */

#ifndef BER_ENCODING_HELPER_HPP
#define BER_ENCODING_HELPER_HPP

#include <string>

#include "BerEncoding.h"
#include "keto/common/StringCodec.hpp"
#include "keto/crypto/Containers.hpp"

namespace keto {
namespace asn1 {

class BerEncodingHelper {
public:
    BerEncodingHelper();
    BerEncodingHelper(const keto::crypto::SecureVector& berEncoding);
    BerEncodingHelper(const BerEncoding_t& berEncoding);
    BerEncodingHelper(const std::string& berEncoding,keto::common::StringEncoding stringEncoding);
    
    BerEncodingHelper(const BerEncodingHelper& orig) = default;
    virtual ~BerEncodingHelper();
    
    BerEncodingHelper& operator=(const BerEncoding_t* berEncoding);
    BerEncodingHelper& operator=(const BerEncoding_t& berEncoding);
    operator BerEncoding_t() const;
    
    BerEncodingHelper& operator =(const keto::crypto::SecureVector& berEncoding);
    operator keto::crypto::SecureVector() const;
    
    BerEncodingHelper& setHash(const std::string& berEncoding,keto::common::StringEncoding stringEncoding);
    std::string getHash(keto::common::StringEncoding stringEncoding);
    
    BerEncodingHelper& setValue(const keto::crypto::SecureVector& berEncoding);
    keto::crypto::SecureVector getValue();
    
private:
    keto::crypto::SecureVector berEncoding;
    
    
    void copyHashToVector(const BerEncoding_t& berEncoding, keto::crypto::SecureVector& vector);
};


}
}


#endif /* HASHHELPER_HPP */

