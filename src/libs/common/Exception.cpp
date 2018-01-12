/* 
 * File:   EnvironmentManager.cpp
 * Author: ubuntu
 * 
 * Created on January 10, 2018, 12:15 PM
 */


#include "keto/common/Exception.hpp"

namespace keto {
namespace common {  

Exception::Exception() noexcept : msg("Exception"){}

Exception::Exception(const std::string& msg) noexcept : msg(msg) {}

Exception::Exception(const Exception& orig) noexcept : std::exception(orig), boost::exception(orig), msg(orig.msg) {}

Exception::~Exception() {
}

Exception& Exception::operator= (const Exception& orig) noexcept {
	this->msg = orig.msg;
	return *this;
}
	
const char* Exception::what() const noexcept {
	return this->msg.c_str();
}


}
}
