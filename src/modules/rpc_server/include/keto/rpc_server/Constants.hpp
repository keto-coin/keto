/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Constants.hpp
 * Author: ubuntu
 *
 * Created on January 22, 2018, 10:21 AM
 */

#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

namespace keto {
namespace rpc_server {

class Constants {
public:
    Constants() = delete;
    Constants(const Constants& orig) = delete;
    virtual ~Constants() = delete;
    
    // rpc address information
    static constexpr const char* IP_ADDRESS = "rpc-server-ip-address";
    static constexpr const char* DEFAULT_IP = "0.0.0.0";
    
    static constexpr const char* PORT_NUMBER = "rpc-server-port-number";
    static constexpr const unsigned short DEFAULT_PORT_NUMBER = 28003;
    
    static constexpr const char* HTTP_THREADS = "rpc-server-thread-number";
    static constexpr const int DEFAULT_HTTP_THREADS = 1;
};
    
}
}

#endif /* CONSTANTS_HPP */

