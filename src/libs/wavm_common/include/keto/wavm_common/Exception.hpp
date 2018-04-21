/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Exception.hpp
 * Author: Brett Chaldecott
 *
 * Created on January 31, 2018, 4:37 PM
 */

#ifndef TRANSACTION_COMMON_EXCEPTION_HPP
#define TRANSACTION_COMMON_EXCEPTION_HPP

#include <string>
#include "keto/common/Exception.hpp"


namespace keto {
namespace wavm_common {

// the keto environment exception base
KETO_DECLARE_EXCEPTION( WavmCommonException, "Wavm common failed." );

// the keto wavm derived exception
KETO_DECLARE_DERIVED_EXCEPTION (WavmCommonException, InvalidContractException , "Failed to parse the contract.");
KETO_DECLARE_DERIVED_EXCEPTION (WavmCommonException, LinkingFailedException , "Linking failed.");
KETO_DECLARE_DERIVED_EXCEPTION (WavmCommonException, MissingEntryPointException , "The entry point to the web assembly was not found.");
KETO_DECLARE_DERIVED_EXCEPTION (WavmCommonException, ContactExecutionFailedException , "Contract execution failed.");

}
}

#endif /* EXCEPTION_HPP */

