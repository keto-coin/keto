/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StringUtils.hpp
 * Author: ubuntu
 *
 * Created on May 19, 2018, 7:36 AM
 */

#ifndef STRINGUTILS_HPP
#define STRINGUTILS_HPP

#include <string>
#include <UTF8String.h>

namespace keto {
namespace asn1 {
namespace StringUtils {
    std::string copyBuffer(const UTF8String_t& buffer);
}
}
}


#endif /* STRINGUTILS_HPP */

