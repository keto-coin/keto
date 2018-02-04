/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AnyInterface.hpp
 * Author: ubuntu
 *
 * Created on February 4, 2018, 5:03 AM
 */

#ifndef ANYINTERFACE_HPP
#define ANYINTERFACE_HPP

#include "ANY.h"

namespace keto {
namespace asn1 {


class AnyInterface {
public:
    virtual void* getPtr() = 0;
    virtual struct asn_TYPE_descriptor_s* getType() = 0;
};

}
}

#endif /* ANYINTERFACE_HPP */

