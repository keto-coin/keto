/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   URLUtils.cpp
 * Author: ubuntu
 * 
 * Created on March 29, 2018, 8:17 AM
 */

#include <sstream>

#include "keto/server_common/URLUtils.hpp"

namespace keto {
namespace server_common {

int hex_decode(const char ch)
{
    int r;
    if ('0' <= ch && ch <= '9')
      r = ch - '0';
    else if ('A' <= ch && ch <= 'F')
      r = ch - 'A' + 0xa;
    else if ('a' <= ch && ch <= 'f')
      r = ch - 'a' + 0xa;
    else
      r = -1;
    return r;
}

std::string hex_decode(const std::string& substr) {
    if (substr.size() < 2) {
        return substr;
    }
    std::stringstream ss;
    ss << ((char)(hex_decode(substr[0]) * 16 + hex_decode(substr[1])));
    return ss.str();
}

std::string URLUtils::unescape(const std::string& escapedString) {
    std::stringstream ss;
    
    for(int index = 0; index < escapedString.size();) {
        char pos = escapedString[index];
        index++;
        if (pos == '%') {
            std::stringstream tmp;
            ss << escapedString.substr(index,2);            
        }else if (pos == '+') {
            ss << " ";
        } else {
            ss << pos;
        }
    }
    
    return ss.str();
}

    
}
}
