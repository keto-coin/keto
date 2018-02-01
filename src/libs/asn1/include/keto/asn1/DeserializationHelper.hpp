/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DeserializationHelper.hpp
 * Author: ubuntu
 *
 * Created on January 31, 2018, 4:07 PM
 */

#ifndef DESERIALIZATIONHELPER_HPP
#define DESERIALIZATIONHELPER_HPP

#include <vector>
#include <stdlib.h>
#include <sstream>
#include <iostream>

#include "ber_decoder.h"
#include "keto/asn1/Exception.hpp"

namespace keto {
namespace asn1 {


template <typename Data> 
class DeserializationHelper {
public:
    DeserializationHelper(const uint8_t* buffer, size_t size,
            const struct asn_TYPE_descriptor_s *type_descriptor) : type_descriptor(type_descriptor) {
        instance = 0;
        asn_dec_rval_t rval = ber_decode(0,type_descriptor,(void **)&instance,buffer,size);
        if (rval.code == RC_WMORE) {
            type_descriptor->op->free_struct(type_descriptor,instance, ASFM_FREE_EVERYTHING);
            BOOST_THROW_EXCEPTION(keto::asn1::IncompleteDataException());
        } else if (rval.code != RC_OK) {
            type_descriptor->op->free_struct(type_descriptor,instance, ASFM_FREE_EVERYTHING);
            std::ostringstream oss;
            oss << "Failed code is [" << rval.code << "] data [" << rval.consumed << "]" ;
            BOOST_THROW_EXCEPTION(keto::asn1::DeserializationException(oss.str()));
        }
    }
    
    DeserializationHelper(const std::vector<uint8_t>& buffer,
            const struct asn_TYPE_descriptor_s *type_descriptor) : type_descriptor(type_descriptor) {
        instance = 0;
        uint8_t byteBuff[buffer.size()];
        std::copy(buffer.begin(), buffer.end(), byteBuff);
        asn_dec_rval_t rval = ber_decode(0,type_descriptor,(void **)&instance,byteBuff,buffer.size());
        if (rval.code == RC_WMORE) {
            type_descriptor->op->free_struct(type_descriptor,instance, ASFM_FREE_EVERYTHING);
            BOOST_THROW_EXCEPTION(keto::asn1::IncompleteDataException());
        } else if (rval.code != RC_OK) {
            type_descriptor->op->free_struct(type_descriptor,instance, ASFM_FREE_EVERYTHING);
            std::ostringstream oss;
            oss << "Failed code is [" << rval.code << "] data [" << rval.consumed << "]" ;
            BOOST_THROW_EXCEPTION(keto::asn1::DeserializationException(oss.str()));
        }
    }
    
    DeserializationHelper(const DeserializationHelper& orig) = delete;
    
    virtual ~DeserializationHelper() {
        ASN_STRUCT_FREE(*type_descriptor,instance);
    }
    
    operator const Data& () {
        return *instance;
    }
    
    operator Data* () {
        return instance;
    }
private:
    const struct asn_TYPE_descriptor_s *type_descriptor;
    Data* instance;
    
};

}
}

#endif /* DESERIALIZATIONHELPER_HPP */

