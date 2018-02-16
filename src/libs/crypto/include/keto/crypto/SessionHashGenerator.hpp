/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SessionHashGenerator.hpp
 * Author: ubuntu
 *
 * Created on February 16, 2018, 6:59 AM
 */

#ifndef SESSIONHASHGENERATOR_HPP
#define SESSIONHASHGENERATOR_HPP

#include <vector>

namespace keto {
namespace crypto {


class SessionHashGenerator {
public:
    SessionHashGenerator(const std::vector<uint8_t>& clientHash,
            const std::vector<uint8_t>& accountHash);
    SessionHashGenerator(const SessionHashGenerator& orig) = default;
    virtual ~SessionHashGenerator();
    
    std::vector<uint8_t> getHash();
    
private:
    std::vector<uint8_t> bytes;

};


}
}

#endif /* SESSIONHASHGENERATOR_HPP */

