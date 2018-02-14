/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Constants.hpp
 * Author: Brett Chaldecott
 *
 * Created on February 13, 2018, 12:52 PM
 */

#ifndef KETO_COMMON_CONSTANTS_HPP
#define KETO_COMMON_CONSTANTS_HPP

namespace keto {
namespace common {


class Constants {
public:
    Constants() = delete;
    Constants(const Constants& orig) = delete;
    virtual ~Constants() = delete;
    
    
    static const int HTTP_VERSION = 11;
    
    static const char* CONTENT_TYPE_HEADING;
    static const char* PROTOBUF_CONTENT_TYPE;
    
};


}
}


#endif /* CONSTANTS_HPP */

