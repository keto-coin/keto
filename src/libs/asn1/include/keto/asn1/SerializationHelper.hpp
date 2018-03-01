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
#include <sstream>
#include <cerrno>
#include <iostream>

#include "der_encoder.h"
#include "keto/asn1/Exception.hpp"
#include "keto/crypto/Containers.hpp"


namespace keto {
namespace asn1 {

template <typename Data> 
class SerializationHelper {
public:
    SerializationHelper(const Data* data, const struct asn_TYPE_descriptor_s *type_descriptor) 
    : type_descriptor(type_descriptor) {
        char buffer[1024];
        size_t errorSize;
        if (asn_check_constraints(type_descriptor,data,buffer,&errorSize) != 0) {
            std::ostringstream oss;
            oss << "The structure is invalid [" << buffer << "]" ;
            BOOST_THROW_EXCEPTION(keto::asn1::SerializationException(oss.str()));
        }
        
        this->buffer.clear();
        asn_enc_rval_t er = 
                 der_encode(type_descriptor, data, &SerializationHelper::serialize, (void *)&this->buffer);
        if(er.encoded == -1) {
            std::ostringstream oss;
            oss << "Cannot encode [" << er.failed_type->name << "] error [" << std::strerror(errno) << "]" ;
            BOOST_THROW_EXCEPTION(keto::asn1::SerializationException(oss.str()));
        }
    }
    
    SerializationHelper(const SerializationHelper& orig) = delete;
    virtual ~SerializationHelper() {};
    
    
    /**
     * This method returns the reference to the vector buffer.
     * 
     * @return The vector buffer containing the serialized object.
     */
    operator std::vector<uint8_t>&() {
        return this->buffer;
    }
    
    /**
     * This method returns the reference to the vector buffer.
     * 
     * @return The vector buffer containing the serialized object.
     */
    operator keto::crypto::SecureVector() {
        keto::crypto::SecureVector vector;
        for (std::vector<uint8_t>::iterator iter = this->buffer.begin();
                iter != this->buffer.end(); iter++) {
            vector.push_back(*iter);
        }
        return vector;
    }
    
    /**
     * This method returns the byte array containing the serialized item.
     * 
     * @return The byte array of characters.
     */
    operator uint8_t*() {
        uint8_t* charBuff = (uint8_t*)malloc(this->buffer.size());
        std::copy(this->buffer.begin(), this->buffer.end(), charBuff);
        return charBuff;
    }
    
    /**
     * The size of the serialized contents.
     * 
     * @return The size of the serialized contents
     */
    size_t size() {
        return this->buffer.size();
    }
private:
    const struct asn_TYPE_descriptor_s *type_descriptor;
    std::vector<uint8_t> buffer;
    
    /**
     * This method is thread safe via the passed in vector buffer.
     * 
     * @param buffer The reference to the buffer to copy.
     * @param size The size of the buffer to copy.
     * @param key The reference to the vector that has to be cast.
     * @return 0 if successful.
     */
    static int serialize(const void *buffer, size_t size, void *key) {
        //std::cout << "The size is " << size << std::endl;
        std::vector<uint8_t>* vecBuffer = (std::vector<uint8_t>*)key;
        uint8_t* byteBuff = (uint8_t*)buffer;
        for (int count = 0; count < size; count++) {
            vecBuffer->push_back(byteBuff[count]);
        }
        //std::cout << "The vect buffer size is :" << vecBuffer->size() << std::endl;
        return 0;
    }
};


}
}


#endif /* SERIALIZATIONHELPER_HPP */

