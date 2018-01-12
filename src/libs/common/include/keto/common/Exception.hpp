/* 
 * File:   Exception.hpp
 * Author: Brett Chaldecott
 *
 * Created on January 11, 2018, 11:08 AM
 */

#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <boost/exception/all.hpp>
#include <boost/throw_exception.hpp>
#include <boost/exception/diagnostic_information.hpp>
#include <exception>

namespace keto {
namespace common {

class Exception : public std::exception, public boost::exception {
public:
    Exception() noexcept;
    Exception(const std::string& msg) noexcept;
    Exception(const Exception& orig) noexcept;
    virtual ~Exception();
    Exception& operator= (const Exception& orig) noexcept;
	
    virtual const char* what() const noexcept;
	
private:
    std::string msg;

};

// This mack
#define KETO_DECLARE_EXCEPTION( TYPE, WHAT ) \
   class TYPE : public keto::common::Exception \
   { \
      public: \
       TYPE() noexcept : Exception(WHAT) {} \
       TYPE( const std::string& msg) noexcept : Exception(msg) {} \
       TYPE( const TYPE& c ) : Exception(c) {} \
   };

#define KETO_DECLARE_DERIVED_EXCEPTION( BASE, TYPE, WHAT ) \
   class TYPE : public BASE \
   { \
      public: \
       TYPE() noexcept : BASE(WHAT) {} \
       TYPE( const std::string& msg) noexcept : BASE(msg) {} \
       TYPE( const TYPE& c ) : BASE(c) {} \
   };

}
}

#endif /* EXCEPTION_HPP */

