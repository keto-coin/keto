/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CloneHelper.hpp
 * Author: ubuntu
 *
 * Created on March 22, 2018, 8:29 AM
 */

#ifndef ASN1_CLONEHELPER_HPP
#define ASN1_CLONEHELPER_HPP

#include <string>
#include <vector>

#include "keto/asn1/SerializationHelper.hpp"
#include "keto/asn1/DeserializationHelper.hpp"

namespace keto {
namespace asn1 {



template <typename Data> 
Data* clone(const Data* data, const struct asn_TYPE_descriptor_s *type_descriptor) {
    return DeserializationHelper<Data>(
        SerializationHelper<Data>(data,type_descriptor).
        operator std::vector<uint8_t>&(),type_descriptor).takePtr();
}

}
}

#endif /* CLONEHELPER_HPP */

