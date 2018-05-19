/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StringUtils.cpp
 * Author: ubuntu
 * 
 * Created on May 19, 2018, 7:36 AM
 */

#include "keto/asn1/StringUtils.hpp"

namespace keto {
namespace asn1 {
namespace StringUtils {
    
std::string copyBuffer(const UTF8String_t& buffer) {
    std::string result;
    for (int count = 0; count < 
            buffer.size; count++) {
        result+= buffer.buf[count];
    }
    return result;
}
}
}
}
