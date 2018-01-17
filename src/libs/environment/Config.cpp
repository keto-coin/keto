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

#include <vector>

#include "keto/environment/Config.hpp"

#include <boost/program_options/cmdline.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>


#include "keto/environment/Constants.hpp"

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;


namespace keto {
    namespace environment {

Config::Config(const std::string& ketoHome, const std::string& file,
            const boost::program_options::options_description& optionDescription,
            int argc, char** argv) :
    ketoHome(ketoHome),file(file) {
    
    // default the log level to info by extending out the option descriptions.
    boost::program_options::options_description localOptions(optionDescription); 
    localOptions.add_options()
            ("log-level,l", boost::program_options::value<boost::log::trivial::severity_level>()->default_value( logging::trivial::info ), "The log level [trace,debug,info,warn,error,critical].");
    
    // parse the command line arguments
    boost::program_options::store(boost::program_options::parse_command_line(
        argc, argv, localOptions), this->variablesMap);
    
    // parse the specified configuration file
    boost::filesystem::path configFilePath = this->ketoHome / Constants::KETO_CONFIG_DIR / file; 
    auto parsedOptions = boost::program_options::parse_config_file<char>(
        configFilePath.string().c_str(), localOptions, true);
    
    // parse the unrecognized program options and add them to the options as known options
    std::vector<std::string> unregognisedOptions = boost::program_options::collect_unrecognized(parsedOptions.options, 
            boost::program_options::include_positional);
    for (auto& option : unregognisedOptions) {
        localOptions.add_options()
            (option.c_str(),option.c_str());
    }
    
    // re-parse the configuration file using the now extended options list.
    boost::program_options::store(boost::program_options::parse_config_file<char>(
        configFilePath.string().c_str(), localOptions, false), this->variablesMap);
    
    // notify the options so as to update the linking appropriatly
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
