/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Exception.hpp
 * Author: ubuntu
 *
 * Created on January 19, 2018, 11:54 AM
 */

#ifndef EVENT_SERVICE_IMPL_EXCEPTION_HPP
#define EVENT_SERVICE_IMPL_EXCEPTION_HPP

#include <string>
#include "keto/common/Exception.hpp"

namespace keto {
namespace event {

KETO_DECLARE_EXCEPTION( EventException, "An exception has occurred with the event service" );

KETO_DECLARE_DERIVED_EXCEPTION (EventException, DuplicateEventHandlerException , "Duplicate event handler.");
KETO_DECLARE_DERIVED_EXCEPTION (EventException, UnknownEventHandlerException , "Unknown event handler.");
    
}
}


#endif /* EXCEPTION_HPP */

