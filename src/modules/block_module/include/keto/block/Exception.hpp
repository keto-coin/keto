/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Exception.hpp
 * Author: ubuntu
 *
 * Created on February 14, 2018, 7:15 AM
 */

#ifndef KETO_BLOCK_EXCEPTION_HPP
#define KETO_BLOCK_EXCEPTION_HPP

#include <string>
#include "keto/common/Exception.hpp"


namespace keto {
namespace block {

// the keto crypto exception base
KETO_DECLARE_EXCEPTION( BlockException, "Block exception." );

// the 
KETO_DECLARE_DERIVED_EXCEPTION (BlockException, PrivateKeyNotConfiguredException , "The server private key configured was not found.");
KETO_DECLARE_DERIVED_EXCEPTION (BlockException, PublicKeyNotConfiguredException , "The server public key configured was not found.");
KETO_DECLARE_DERIVED_EXCEPTION (BlockException, BlockProducerTerminatedException , "The block producer has been terminated.");

    
}
}


#endif /* EXCEPTION_HPP */

