/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AnyHelper.hpp
 * Author: brett chaldecott
 *
 * Created on February 3, 2018, 11:15 AM
 */

#ifndef ANYHELPER_HPP
#define ANYHELPER_HPP

#include "ANY.h"

#include <vector>
#include <stdlib.h>
#include <sstream>
#include <cerrno>
#include <iostream>

#include "der_encoder.h"
#include "keto/asn1/Exception.hpp"
#include "keto/asn1/AnyInterface.hpp"


namespace keto {
namespace asn1 {


class AnyHelper {
public:
    /**
     * This constructor takes a reference to an any interface but does not take
     * ownership of the pointer.
     * 
     * @param anyInterface The pointer to the any interface
     */
    AnyHelper(AnyInterface* anyInterface);
    
    /**
     * The constructor taking a pointer reference to 
     * @param any
     */
    AnyHelper(ANY_t* any);
    
    /**
     * The default copy constructor
     * @param orig
     */
    AnyHelper(const AnyHelper& orig) = default;
    
    virtual ~AnyHelper();
    
    /**
     * This method attempts to extract the any value. If 
     * @param type_descriptor
     * @return NULL if extraction failed. Object pointer reference if successful.
     */
    template<typename T>
    T* extract (struct asn_TYPE_descriptor_s *type_descriptor) {
        if (!any) {
            BOOST_THROW_EXCEPTION(keto::asn1::InvalidAnyValueException());
        }
        T* result = 0;
        if (-1 == ANY_to_type(any, type_descriptor, (void**)&result)) {
            return NULL;
        }
        return result;
    }
    
    /**
     * This method returns a reference to the any object
     * @return Returns a structure containing the memory of the serialized pointer
     */
    operator ANY_t();
    
private: 
    AnyInterface* anyInterface;
    ANY_t* any;

};


}
}


#endif /* ANYHELPER_HPP */

