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
    
    static constexpr const char* KETO_VERSION = "version";
    static constexpr const char* KETO_HELP = "help";
    static constexpr const char* KETO_LOG_FILE = "log-file";
    static constexpr const char* KETO_LOG_LEVEL = "log-level";
    
    static constexpr const char* KETO_HOME = "KETO_HOME";
    
    // the keto directories
    static constexpr const char* KETO_CONFIG_DIR = "config";
    static constexpr const char* KETO_LOG_DIR = "log";
    
    // the keto configuration file files
    static constexpr const char* KETOD_CONFIG_FILE = "config.ini";
    static constexpr const char* KETO_CLI_CONFIG_FILE = "cli_config.ini";
    static constexpr const char* KETO_CONTRACT_TOOLS_FILE = "keto_contract_tools.ini";
    
    // the keto configuration file files
    static constexpr const char* KETOD_LOG_FILE = "ketod_%N.log";
    static constexpr const char* KETO_CLI_LOG_FILE = "keto_cli_%N.log";

private:
};

}
}
#endif /* CONSTANTS_HPP */

