/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SignatureVerification.hpp
 * Author: ubuntu
 *
 * Created on February 6, 2018, 12:07 PM
 */

#ifndef SIGNATUREVERIFICATION_HPP
#define SIGNATUREVERIFICATION_HPP

#include <vector>
#include <memory>

namespace keto {
namespace crypto {


class SignatureVerification {
public:
    SignatureVerification(std::vector<uint8_t>& key);
    SignatureVerification(const SignatureVerification& orig) = default;
    virtual ~SignatureVerification();
    
    bool check(std::vector<uint8_t>& signature);
private:
    std::vector<uint8_t> key;

};


}
}

#endif /* SIGNATUREVERIFICATION_HPP */

