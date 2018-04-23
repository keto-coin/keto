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
    
std::string WavmUtils::readUserString(Runtime::MemoryInstance* memory,I32 stringAddress) {
    // Validate the path name and make a local copy of it.
    std::string pathString;
    if (0 == Runtime::memoryRef<char>(memory,stringAddress + 3) ) {
        int size = Runtime::memoryRef<char>(memory,stringAddress);
        size += Runtime::memoryRef<char>(memory,stringAddress+1) * 100;
        size += Runtime::memoryRef<char>(memory,stringAddress+2) * 10000;
        for (int index = 0; index < (size * 2); index++) {
            pathString += (int)Runtime::memoryRef<char>(memory,stringAddress + 4 + index);
        }
    } else {
        int index = 0;
        while(true)
        {
            int c = Runtime::memoryRef<char>(memory,stringAddress + index);
            if(c == 0) { 
                break; 
            } else {
                pathString += c;
            }
            index ++;
        };
    }
    return pathString;
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