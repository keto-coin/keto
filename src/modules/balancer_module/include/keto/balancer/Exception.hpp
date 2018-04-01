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

#ifndef KETO_ROUTER_MODULE_EXCEPTION_HPP
#define KETO_ROUTER_MODULE_EXCEPTION_HPP

#include <string>
#include "keto/common/Exception.hpp"


namespace keto {
namespace router {

// the keto crypto exception base
KETO_DECLARE_EXCEPTION( BalancerModuleException, "Keto Balancer Module Exception." );

// the 
//KETO_DECLARE_DERIVED_EXCEPTION (BalancerModuleException, NoServicesRegisteredException , "No services registered.");

}
}

#endif /* EXCEPTION_HPP */

