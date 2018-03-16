/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Constants.hpp
 * Author: ubuntu
 *
 * Created on February 27, 2018, 7:50 AM
 */

#ifndef BLOCK_CONSTANTS_HPP
#define BLOCK_CONSTANTS_HPP

#include <vector>
#include <string>

namespace keto {
namespace block_db {


class
Constants {
public:
    
    // string constants
    static const char* BLOCKS_INDEX;
    static const char* TRANSACTIONS_INDEX;
    static const char* ACCOUNTS_INDEX;
    static const char* CHILD_INDEX;
    
    // boot constants
    static const char* GENESIS_KEY;
    
    
    static const std::vector<std::string> DB_LIST;
    
    
    
};


}
}

#endif /* CONSTANTS_HPP */

