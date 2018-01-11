/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Exception.cpp
 * Author: ubuntu
 * 
 * Created on January 11, 2018, 11:08 AM
 */

#include "keto/common/Exception.hpp"
#include "include/keto/common/Exception.hpp"

namespace keto {
namespace common {

Exception::Exception() noexcept {
}

Exception::Exception(std::string msg) noexcept : msg(msg) {
}

Exception::Exception(const Exception& orig) noexcept : std::exception(orig), boost::exception(orig), msg(orig.msg) {
    
}

const char* Exception::what() const noexcept {
    return this->msg.c_str();
}

}
}