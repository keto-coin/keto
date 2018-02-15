/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Exception.hpp
 * Author: ubuntu
 *
 * Created on February 15, 2018, 6:43 PM
 */

#ifndef KETO_HTTP_SERVER_SESSION_EXCEPTION_HPP
#define KETO_HTTP_SERVER_SESSION_EXCEPTION_HPP

#include <string>
#include "keto/common/Exception.hpp"

namespace keto {
namespace server_session {

// the keto crypto exception base
KETO_DECLARE_EXCEPTION( HttpServerSessionException, "Keto Http Server Session." );

// the 
KETO_DECLARE_DERIVED_EXCEPTION (HttpServerSessionException, MessageSerializationException , "The server message failed serialize.");
KETO_DECLARE_DERIVED_EXCEPTION (HttpServerSessionException, MessageDeserializationException , "The server message failed deserialize.");
    
}
}



#endif /* EXCEPTION_HPP */

