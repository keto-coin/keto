    /*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Constants.hpp
 * Author: ubuntu
 *
 * Created on January 21, 2018, 7:02 AM
 */

#ifndef KETO_BALANCER_CONSTANTS_HPP
#define KETO_BALANCER_CONSTANTS_HPP

namespace keto {
namespace balancer {

class Constants {
public:
    Constants() = delete;
    Constants(const Constants& orig) = delete;
    virtual ~Constants() = delete;
    
    // document root
    static constexpr const char* DEFAULT_BLOCK = "default_block";
    
    
};
    
}
}


#endif /* CONSTANTS_HPP */

