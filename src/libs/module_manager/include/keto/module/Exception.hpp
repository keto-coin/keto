/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Exception.hpp
 * Author: Brett Chaldecott
 *
 * Created on January 16, 2018, 11:06 AM
 */

#ifndef KETO_MODULE_EXCEPTION_HPP
#define KETO_MODULE_EXCEPTION_HPP

#include <string>
#include "keto/common/Exception.hpp"


namespace keto {
namespace module {
        
// the keto module exception base
KETO_DECLARE_EXCEPTION( ModuleException, "An exception has occurred with a module" );
KETO_DECLARE_EXCEPTION( ModuleManagerException, "Environment could not be configure correctly" );


// the keto module derived exception
KETO_DECLARE_DERIVED_EXCEPTION (ModuleLoadException , ModuleManagerException, "Failed to load a module.");
KETO_DECLARE_DERIVED_EXCEPTION (ModuleUnloadException , ModuleManagerException, "Failed to unload a module.");
KETO_DECLARE_DERIVED_EXCEPTION (ModuleMonitorException , ModuleManagerException, "An exception while monitoring the modules");        
KETO_DECLARE_DERIVED_EXCEPTION (ModuleSharedDirException , ModuleManagerException, "The KETO_HOME/shared directory does not exist");
KETO_DECLARE_DERIVED_EXCEPTION (ModuleTmpDirException , ModuleManagerException, "The KETO_HOME/tmp directory failure");
}
}


#endif /* EXCEPTION_HPP */

