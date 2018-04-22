/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   WavmUtils.hpp
 * Author: ubuntu
 *
 * Created on April 22, 2018, 5:42 PM
 */

#ifndef WAVMUTILS_HPP
#define WAVMUTILS_HPP

#include <string>

#include "Inline/BasicTypes.h"
#include "Runtime/Runtime.h"

namespace keto {
namespace wavm_common {

class WavmUtils {
public:
    WavmUtils() = delete;
    WavmUtils(const WavmUtils& orig) = delete;
    virtual ~WavmUtils() = delete;
    
    static std::string readUserString(Runtime::MemoryInstance* memory,I32 stringAddress);
private:

};

}
}


#endif /* WAVMUTILS_HPP */

