/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: ubuntu
 *
 * Created on May 7, 2018, 10:14 AM
 */

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/error.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <cstdlib>
#include <iostream>
#include <string>
#include <boost/exception/exception.hpp>
#include <boost/exception/diagnostic_information.hpp>
#include <boost/exception_ptr.hpp> 

#include <botan/hex.h>
#include <botan/base64.h>

#include "keto/common/MetaInfo.hpp"
#include "keto/common/Log.hpp"
#include "keto/common/Exception.hpp"
#include "keto/common/StringCodec.hpp"
#include "keto/environment/EnvironmentManager.hpp"
#include "keto/environment/Constants.hpp"
#include "keto/ssl/RootCertificate.hpp"
#include "keto/server_common/VectorUtils.hpp"

#include "keto/contract/Constants.hpp"

#include "keto/account_utils/AccountGenerator.hpp"


namespace ketoEnv = keto::environment;
namespace ketoCommon = keto::common;


boost::program_options::options_description generateOptionDescriptions() {
    boost::program_options::options_description optionDescripion;
    
    optionDescripion.add_options()
            ("help,h", "Print this help message and exit.")
            ("version,v", "Print version information.")
            ("encodeWast,e", "Encode a wast file as hexadecimal.")
            ("generateHash,g", "Generate a contract hash code.")
            ("source,s", po::value<std::string>(),"Source file.")
            ("target,t",po::value<std::string>(), "Target file.");
    
    return optionDescripion;
}

void encodeWastFile(std::shared_ptr<ketoEnv::Config> config,
        boost::program_options::options_description optionDescription) {
    std::cout <<  "Encode a wast file" << std::endl;
    
    // retrieve source account hash
    if (!config->getVariablesMap().count(keto::contract::Constants::SOURCE_FILE)) {
        std::cerr << "Please provide the source file [" << 
                keto::contract::Constants::SOURCE_FILE << "]" << std::endl;
        std::cout <<  optionDescription << std::endl;
        return;
    }
    boost::filesystem::path sourceFile = config->getVariablesMap()[keto::contract::Constants::SOURCE_FILE].as<std::string>();
    
    if (!boost::filesystem::exists(sourceFile)) {
        std::cerr << "The source file does not exist [" << 
                sourceFile << "]" << std::endl;
        return;
    }
    
    if (!config->getVariablesMap().count(keto::contract::Constants::TARGET_FILE)) {
        std::cerr << "Please provide the target file [" << 
                keto::contract::Constants::TARGET_FILE << "]" << std::endl;
        std::cout <<  optionDescription << std::endl;
        return;
    }
    boost::filesystem::path targetFile = config->getVariablesMap()[keto::contract::Constants::TARGET_FILE].as<std::string>();
    
    std::ifstream in(sourceFile.string());
    std::string line;
    std::stringstream ss;
    while (!in.eof()) {
        in >> line;
        ss << line << std::endl;
    }
    in.close();
    
    std::ofstream out(targetFile.string());
    out << Botan::hex_encode(
            keto::server_common::VectorUtils().copyStringToVector(ss.str()));
    out.close();
}

void generateHash(std::shared_ptr<ketoEnv::Config> config,
        boost::program_options::options_description optionDescription) {
    std::cout << 
            Botan::hex_encode(
            (keto::account_utils::AccountGenerator().getAccountHash()),true) << std::endl;
}

/*
 * The main method responsible for  
 */
int main(int argc, char** argv) {
    
    try {
        boost::program_options::options_description optionDescription =
                generateOptionDescriptions();
        
        std::shared_ptr<ketoEnv::EnvironmentManager> manager = 
                keto::environment::EnvironmentManager::init(
                keto::environment::Constants::KETO_CONTRACT_TOOLS_FILE,
                optionDescription,argc,argv);
        
        std::shared_ptr<ketoEnv::Config> config = manager->getConfig();
        
        if (config->getVariablesMap().count(ketoEnv::Constants::KETO_VERSION)) {
            std::cout << ketoCommon::MetaInfo::VERSION << std::endl;
            return 0;
        }
        
        if (config->getVariablesMap().count(ketoEnv::Constants::KETO_HELP)) {
            std::cout <<  optionDescription << std::endl;
            return 0;
        }
        
        if (config->getVariablesMap().count(keto::contract::Constants::ENCODE_WAST)) {
            encodeWastFile(config,optionDescription);
            return 0;
        }else if (config->getVariablesMap().count(keto::contract::Constants::GENERATE_HASH)) {
            generateHash(config,optionDescription);
            return 0;
        }
        
    } catch (keto::common::Exception& ex) {
        KETO_LOG_ERROR << "Failed to start because : " << ex.what();
        KETO_LOG_ERROR << "Cause: " << boost::diagnostic_information(ex,true);
        return -1;
    } catch (boost::exception& ex) {
        KETO_LOG_ERROR << "Failed to start because : " << boost::diagnostic_information(ex,true);
        return -1;
    } catch (std::exception& ex) {
        KETO_LOG_ERROR << "Failed to start because : " << ex.what();
        return -1;
    } catch (...) {
        KETO_LOG_ERROR << "Failed to start unknown error.";
        return -1;
    }
    
    return 0;
}

