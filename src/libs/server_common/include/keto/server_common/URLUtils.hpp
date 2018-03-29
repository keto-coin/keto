/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   URLUtils.hpp
 * Author: ubuntu
 *
 * Created on March 29, 2018, 8:17 AM
 */

#ifndef URLUTILS_HPP
#define URLUTILS_HPP

namespace keto {
namespace server_common {

class URLUtils {
public:
    static std::string unescape(const std::string& escapedString);
      
private:
};

}
}

#endif /* URLUTILS_HPP */

