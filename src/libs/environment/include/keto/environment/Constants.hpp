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
    
    // the log configuration item
    static constexpr const char* LOG_CONFIG = "log-config";
    
    // the keto directories
    static constexpr const char* KETO_CONFIG_DIR = "config";
    
    // the keto configuration file files
    static constexpr const char* KETOD_CONFIG_FILE = "config.ini";
    static constexpr const char* KETO_CLI_CONFIG_FILE = "cli_config.ini";

private:
};

}
}
#endif /* CONSTANTS_HPP */

