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

private:

};


}
}

#endif /* CONSTANTS_HPP */

