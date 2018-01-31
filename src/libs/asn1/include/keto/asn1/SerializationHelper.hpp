/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SerializationHelper.hpp
 * Author: ubuntu
 *
 * Created on January 31, 2018, 3:36 PM
 */

#ifndef SERIALIZATIONHELPER_HPP
#define SERIALIZATIONHELPER_HPP

#include <vector>
#include <stdlib.h>

#include "der_encoder.h"

namespace keto {
namespace asn1 {

template <typename Data> 
class SerializationHelper {
public:
    SerializationHelper(Data* data, const struct asn_TYPE_descriptor_s *type_descriptor) 
    : type_descriptor(type_descriptor) {
         der_encode(type_descriptor, data, &SerializationHelper::serialize, (void *)&this->buffer);
    }
    
    SerializationHelper(const SerializationHelper& orig) = delete;
    virtual ~SerializationHelper() {};
    
    operator std::vector<unsigned char>() {
        return buffer;
    }
    
    operator unsigned char*() {
        unsigned char* charBuff = (unsigned char*)malloc(this->buffer.size());
        std::copy(this->buffer.begin(), this->buffer.end(), charBuff);
        return charBuff;
    }
private:
    const struct asn_TYPE_descriptor_s *type_descriptor;
    std::vector<unsigned char> buffer;
    
    static int serialize(const void *buffer, size_t size, void *key) {
        std::vector<unsigned char>* vecBuffer = (std::vector<unsigned char>*)key;
        unsigned char* charBuff = (unsigned char*)buffer;
        for (int count = 0; count < size; count++) {
            vecBuffer->push_back((unsigned char)charBuff[count]);
        }
        return 0;
    }
};


}
}


#endif /* SERIALIZATIONHELPER_HPP */

