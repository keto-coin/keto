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

#ifndef CHAIN_COMMON_EXCEPTION_HPP
#define CHAIN_COMMON_EXCEPTION_HPP

#include <string>
#include "keto/common/Exception.hpp"


namespace keto {
namespace chain_common {

// the keto environment exception base
KETO_DECLARE_EXCEPTION( ChainCommonException, "Chain common exception." );

// the keto environment derived exception
KETO_DECLARE_DERIVED_EXCEPTION (ChainCommonException, ActionSequenceAddFailedException , "Failed to add the action to the transaction.");


}
}

#endif /* EXCEPTION_HPP */

