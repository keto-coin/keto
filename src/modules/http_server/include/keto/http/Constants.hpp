    /*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Constants.hpp
 * Author: ubuntu
 *
 * Created on January 21, 2018, 7:02 AM
 */

#ifndef KETO_HTTP_CONSTANTS_HPP
#define KETO_HTTP_CONSTANTS_HPP

namespace keto {
namespace http {

class Constants {
public:
    Constants() = delete;
    Constants(const Constants& orig) = delete;
    virtual ~Constants() = delete;
    
    // document root
    static constexpr const char* DOCUMENT_ROOT = "document-root";
    static constexpr const char* DOCUMENT_ROOT_DEFAULT = "document_root";
    
    static constexpr const char* IP_ADDRESS = "http-ip-address";
    static constexpr const char* DEFAULT_IP = "0.0.0.0";
    
    static constexpr const char* PORT_NUMBER = "http-port-number";
    static constexpr const unsigned short DEFAULT_PORT_NUMBER = 8080;
    
    static constexpr const char* HTTP_THREADS = "http-thread-number";
    static constexpr const int DEFAULT_HTTP_THREADS = 1;
    
};
    
}
}


#endif /* CONSTANTS_HPP */

