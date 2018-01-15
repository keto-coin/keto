/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Config.cpp
 * Author: ubuntu
 * 
 * Created on January 12, 2018, 7:08 PM
 */

#include "keto/environment/Config.hpp"

#include <boost/program_options/cmdline.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>

#include "keto/environment/Constants.hpp"

namespace keto {
    namespace environment {

Config::Config(const std::string& ketoHome, const std::string& file,
            const boost::program_options::options_description& optionDescription,
            int argc, char** argv) :
    ketoHome(ketoHome),file(file) {
    
    // parse the command line arguments
    boost::program_options::store(boost::program_options::parse_command_line(
        argc, argv, optionDescription), this->variablesMap);
    
    // parse the configuration file
    boost::filesystem::path configFilePath = this->ketoHome / Constants::KETO_CONFIG_DIR / file; 
    
    boost::program_options::store(boost::program_options::parse_config_file<char>(
        configFilePath.string().c_str(), optionDescription,true), this->variablesMap);
    
    boost::program_options::notify(this->variablesMap);
}

Config::~Config() {
}

std::string Config::getFile() {
    return this->file;
}

const boost::program_options::variables_map& Config::getVariablesMap() {
    return this->variablesMap;
}

}
}
