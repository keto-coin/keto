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

#include "ber_decoder.h"
#include "Exception.hpp"

namespace keto {
namespace asn1 {


template <typename Data> 
class DeserializationHelper {
public:
    DeserializationHelper(const unsigned char* buffer, 
            const struct asn_TYPE_descriptor_s *type_descriptor) :type_descriptor(type_descriptor) {
        instance = 0;
        asn_dec_rval_t rval;
        rval = ber_decode(0,type_descriptor,(void **)&instance,buffer,sizeof(buffer));
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
    
    DeserializationHelper(const std::vector<unsigned char> buffer,
            const struct asn_TYPE_descriptor_s *type_descriptor) : type_descriptor(type_descriptor) {
        unsigned char* charBuff = (unsigned char*)malloc(buffer.size());
        std::copy(buffer.begin(), buffer.end(), charBuff);
        asn_dec_rval_t rval = ber_decode(0,type_descriptor,(void **)&instance,charBuff,buffer.size());
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
        type_descriptor->op->free_struct(type_descriptor,instance, ASFM_FREE_EVERYTHING);
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

