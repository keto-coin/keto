/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Exception.hpp
 * Author: ubuntu
 *
 * Created on January 11, 2018, 11:08 AM
 */

#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <boost/exception/all.hpp>
#include <boost/throw_exception.hpp>
#include <exception>

namespace keto {
namespace common {

class Exception : public std::exception, public boost::exception {
public:
    Exception() noexcept;
    Exception(std::string msg) noexcept;
    Exception(const Exception& orig) noexcept;
    virtual ~Exception();
    Exception& operator= (const Exception&) noexcept;
    virtual const char* what() const noexcept;
private:
    std::string msg;

};

}
}

#endif /* EXCEPTION_HPP */

