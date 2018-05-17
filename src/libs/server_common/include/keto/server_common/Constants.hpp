/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Constants.hpp
 * Author: ubuntu
 *
 * Created on February 16, 2018, 8:18 AM
 */

#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

namespace keto {
namespace server_common {

class Constants {
public:
    Constants() = delete;
    Constants(const Constants& orig) = delete;
    virtual ~Constants() = delete;
    
    static const char* PUBLIC_KEY_DIR;
    static const char* ACCOUNT_HASH;
    
    // keys for server
    static const char* PRIVATE_KEY;
    static const char* PUBLIC_KEY;

    
    class SERVICE {
    public:
        static const char* ROUTE;
        static const char* BALANCE;
        static const char* BLOCK;
        static const char* PROCESS;
    };
    
    class CONTRACTS {
    public:
        static const char* BASE_ACCOUNT_CONTRACT;
        
    };
    
    class ACCOUNT_ACTIONS {
    public:
        static const char* DEBIT;
        static const char* CREDIT;
    };
    
private:

};


}
}

#endif /* CONSTANTS_HPP */

