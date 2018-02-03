/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HashHelper.hpp
 * Author: ubuntu
 *
 * Created on February 2, 2018, 4:03 AM
 */

#ifndef HASHHELPER_HPP
#define HASHHELPER_HPP

#include <botan/secmem.h>

namespace keto {
namespace asn1 {

class HashHelper {
public:
    HashHelper();
    HashHelper(const HashHelper& orig);
    virtual ~HashHelper();
    
    
private:
    Botan::secure_vector<uint8_t> hash;
    
};


}
}


#endif /* HASHHELPER_HPP */

