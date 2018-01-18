/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Config.hpp
 * Author: Brett Chaldecott
 *
 * Created on January 12, 2018, 7:08 PM
 * This object contains the logic to initialize the configuration for the environment
 * 
 */

#ifndef CONFIG_HPP
#define CONFIG_HPP

// std include
#include <memory>

// boost includes
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/filesystem/path.hpp>

namespace keto {
namespace environment {


class Config {
public:
    Config(const boost::filesystem::path& ketoHome, const std::string& file,
            const boost::program_options::options_description& optionDescription,
            int argc, char** argv);
    Config(const Config& orig) = delete;
    virtual ~Config();
    
    std::string getFile();
    
    /**
     * This method returns the variables map
     * 
     * @return the 
     */
    const boost::program_options::variables_map& getVariablesMap();
    
private:
    // private member variales
    const boost::filesystem::path ketoHome;
    const std::string file;
    boost::program_options::variables_map variablesMap;
    
};

    
}
}

#endif /* CONFIG_HPP */

