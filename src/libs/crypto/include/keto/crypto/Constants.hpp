/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Constants.hpp
 * Author: Brett Chaldecott
 *
 * Created on February 6, 2018, 11:09 AM
 */

#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

namespace keto {
namespace crypto {


class Constants {
public:
    static constexpr const char* SIGNATURE_TYPE = "EMSA3(SHA-256)";
    static constexpr const char* HASH_TYPE = "SHA-256";
    
};

}
}

#endif /* CONSTANTS_HPP */

