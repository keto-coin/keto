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
    
    static constexpr const char* ACTION = "action";
    static constexpr const char* PARENT = "parent";
    static constexpr const char* SOURCE_ACCOUNT = "source";
    static constexpr const char* TARGET_ACCOUNT = "target";
    static constexpr const char* VALUE = "value";
    
    // commands
    static constexpr const char* KETO_TRANSACTION_GEN = "transgen";
    static constexpr const char* KETO_ACCOUNT_GEN = "accgen";
    static constexpr const char* KETO_SESSION_GEN = "sessiongen";
    static constexpr const char* KETO_ACCOUNT_KEY = "account_key";
    
    static const int HTTP_VERSION = 11;
    
    
};



}
}

#endif /* CONSTANTS_HPP */

