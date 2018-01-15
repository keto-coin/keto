
#include <iostream>
#include <boost/exception/exception.hpp>
#include <boost/exception/diagnostic_information.hpp>
#include <boost/exception_ptr.hpp> 

#include "keto/common/MetaInfo.hpp"
#include "keto/common/Log.hpp"
#include "keto/common/Exception.hpp"
#include "keto/environment/EnvironmentManager.hpp"
#include "keto/environment/Constants.hpp"

namespace ketoEnv = keto::environment;
namespace ketoCommon = keto::common;


boost::program_options::options_description generateOptionDescriptions() {
    boost::program_options::options_description optionDescripion;
    
    optionDescripion.add_options()
            ("help,h", "Print this help message and exit.")
            ("version,v", "Print version information.");
    
    return optionDescripion;
}

/**
 * The CLI main file
 * 
 * @param argc
 * @param argv
 * @return 
 */
int main(int argc, char** argv)
{
    try {
        boost::program_options::options_description optionDescription =
                generateOptionDescriptions();
        
        std::shared_ptr<ketoEnv::EnvironmentManager> manager = 
                keto::environment::EnvironmentManager::init(
                keto::environment::Constants::KETO_CLI_CONFIG_FILE,
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
        
        
        KETO_LOG_INFO << "CLI Executed";
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
}
