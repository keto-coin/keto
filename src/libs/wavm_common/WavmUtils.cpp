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
#include <iostream>

#include "keto/common/Log.hpp"
#include "keto/wavm_common/WavmUtils.hpp"


namespace keto {
namespace wavm_common {
    
std::string WavmUtils::readCString(Runtime::MemoryInstance* memory,I32 stringAddress) {
    // Validate the path name and make a local copy of it.
    std::string returnString;
    int index = 0;
    while(true)
    {
        int c = Runtime::memoryRef<char>(memory,stringAddress + index);
        if(c == 0) { 
            break; 
        } else {
            returnString += c;
        }
        index ++;
    };
    return returnString;
}


std::string WavmUtils::readTypeScriptString(Runtime::MemoryInstance* memory,I32 stringAddress) {
    // Validate the path name and make a local copy of it.
    std::string returnString;
    std::cout << "Get the size : " << stringAddress << std::endl;
    int size = Runtime::memoryRef<char>(memory,stringAddress);
    std::cout << "Get the size 2 " << size << std::endl;
    size += Runtime::memoryRef<char>(memory,stringAddress+1) * 100;
    std::cout << "Get the size 3 " << size << std::endl;
    size += Runtime::memoryRef<char>(memory,stringAddress+2) * 10000;
    std::cout << "Get the size 4 " << size << std::endl;
    for (int index = 0; index < (size * 2); index++) {
        std::cout << "The pos [" << (4 + index) <<  "] : " << (int)Runtime::memoryRef<char>(memory,stringAddress + 4 + index) << std::endl;
        returnString += (int)Runtime::memoryRef<char>(memory,stringAddress + 4 + index);
    }
    std::cout << "Get the string : " << returnString << std::endl;
    return returnString;
}


void WavmUtils::log(uint32_t intLevel,const std::string& msg) {
    switch(intLevel) {
        case 1 :
            KETO_LOG_DEBUG << msg;
            break;
        case 2 :
            KETO_LOG_INFO << msg;
            break;
        case 3 :
            KETO_LOG_WARNING << msg;
            break;
        case 4 :
            KETO_LOG_ERROR << msg;
            break;
        case 5 :
            KETO_LOG_FATAL << msg;
            break;
    };
}
    
}
}