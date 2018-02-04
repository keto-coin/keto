/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Containers.hpp
 * Author: ubuntu
 *
 * Created on February 4, 2018, 4:36 PM
 */

#ifndef KETO_CRYPTO_CONTAINERS_HPP
#define KETO_CRYPTO_CONTAINERS_HPP

#include <botan/secmem.h>

namespace keto {
namespace crypto {

using SecureVector = Botan::secure_vector<uint8_t>;
    
}
}


#endif /* CONTAINERS_HPP */

