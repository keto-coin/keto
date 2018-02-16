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

#ifndef KETO_CRYPTO_EXCEPTION_HPP
#define KETO_CRYPTO_EXCEPTION_HPP

#include <string>
#include "keto/common/Exception.hpp"


namespace keto {
namespace crypto {

// the keto crypto exception base
KETO_DECLARE_EXCEPTION( CyptoCommonException, "Crypto common exception." );

// the 
KETO_DECLARE_DERIVED_EXCEPTION (CyptoCommonException, PrivateKeyNotConfiguredException , "Key loader has no private key configured to load.");
KETO_DECLARE_DERIVED_EXCEPTION (CyptoCommonException, PublicKeyNotConfiguredException , "Key loader has no public key configured to load.");
KETO_DECLARE_DERIVED_EXCEPTION (CyptoCommonException, InvalidKeyPathException , "The specified key path is invalid.");
KETO_DECLARE_DERIVED_EXCEPTION (CyptoCommonException, KeyLoaderNotInitializedException , "The key loader has not been initialized.");

    
}
}


#endif /* EXCEPTION_HPP */

