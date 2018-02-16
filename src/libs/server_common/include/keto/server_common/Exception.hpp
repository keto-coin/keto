/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Exception.hpp
 * Author: ubuntu
 *
 * Created on February 16, 2018, 8:59 AM
 */

#ifndef KETO_SERVER_COMMON_EXCEPTION_HPP
#define KETO_SERVER_COMMON_EXCEPTION_HPP

#include <string>
#include "keto/common/Exception.hpp"


namespace keto {
namespace server_common {

// the keto crypto exception base
KETO_DECLARE_EXCEPTION( ServerCommonException, "Keto Server Common Exception." );

// the 
KETO_DECLARE_DERIVED_EXCEPTION (ServerCommonException, NoPublicKeyDirectoryConfiguredException , "No public key configuration directory has been provided.");
KETO_DECLARE_DERIVED_EXCEPTION (ServerCommonException, InvalidPublicKeyDirectoryException , "Could not retrieve the public key directory.");
KETO_DECLARE_DERIVED_EXCEPTION (ServerCommonException, NoServerAccountConfiguredException , "No server account has been configured.");

}
}

#endif /* EXCEPTION_HPP */

