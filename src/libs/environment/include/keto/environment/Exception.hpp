


#ifndef ENVIRONMENT_EXCEPTION_HPP
#define ENVIRONMENT_EXCEPTION_HPP

#include <string>
#include "keto/common/Exception.hpp"

namespace keto {
namespace environment {

// the keto environment exception base
KETO_DECLARE_EXCEPTION( EnvironmentException, "Environment could not be configure correctly" );

// the keto environment derived exception
KETO_DECLARE_DERIVED_EXCEPTION (EnvironmentException , HomeNotSet, "KETO_HOME environmental variable has not been set.");

}
}

#endif
