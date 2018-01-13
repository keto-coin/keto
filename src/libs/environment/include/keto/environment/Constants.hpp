/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Constants.hpp
 * Author: Brett Chaldecott
 *
 * Created on January 11, 2018, 9:47 AM
 */

#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

namespace keto {
namespace environment {


class Constants {
public:
    static constexpr const char* KETO_HOME = "KETO_HOME";
    static constexpr const char* CONFIG_PATH = "config/config.in";
    
    // log configuration
    static constexpr const char* LOG_CONFIG_PATH = "log-path";
    
private:
};

}
}
#endif /* CONSTANTS_HPP */

