/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   WavmUtils.cpp
 * Author: ubuntu
 * 
 * Created on April 22, 2018, 5:42 PM
 */

#include <string>

#include "keto/wavm_common/WavmUtils.hpp"


namespace keto {
namespace wavm_common {
    
std::string WavmUtils::readUserString(Runtime::MemoryInstance* memory,I32 stringAddress) {
    // Validate the path name and make a local copy of it.
    std::string pathString;
    while(true)
    {
        const char c = Runtime::memoryRef<char>(memory,stringAddress + 
            pathString.size());
        
        if(c == 0) { break; }
        else { pathString += c; }
    };

    return pathString;
}
    
}
}