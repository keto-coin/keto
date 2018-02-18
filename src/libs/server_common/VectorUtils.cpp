/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   VectorUtils.cpp
 * Author: ubuntu
 * 
 * Created on February 16, 2018, 11:21 AM
 */

#include <vector>
#include <sstream>
#include <iterator>

#include "keto/server_common/VectorUtils.hpp"

namespace keto {
namespace server_common {

VectorUtils::VectorUtils() {
}

VectorUtils::~VectorUtils() {
}

std::vector<uint8_t> VectorUtils::copyStringToVector(const std::string& str) {
    std::vector<uint8_t> result;
    for (int index = 0; index < str.size(); index++) {
        result.push_back(str[index]);
    }
    return result;
}

std::string VectorUtils::copyVectorToString(const std::vector<uint8_t>& vec) {
    std::stringstream ss; 
    std::copy(vec.begin(), vec.end(),
         std::ostream_iterator<uint8_t>(ss));
    return ss.str();
}

}
}
