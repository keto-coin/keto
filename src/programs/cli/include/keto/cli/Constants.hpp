/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Constants.hpp
 * Author: ubuntu
 *
 * Created on February 13, 2018, 7:28 AM
 */

#ifndef KETO_CLI_CONSTANTS_HPP
#define KETO_CLI_CONSTANTS_HPP

namespace keto {
namespace cli {


class Constants {
public:
    static constexpr const char* KETOD_SERVER = "ketod_server";
    static constexpr const char* KETOD_PORT = "ketod_port";
    static constexpr const char* PRIVATE_KEY = "private_key";
    static constexpr const char* PUBLIC_KEY = "public_key";
    
    static const int HTTP_VERSION = 11;
    
    
};



}
}

#endif /* CONSTANTS_HPP */
