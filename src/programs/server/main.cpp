
#include <signal.h>
#include <iostream>
#include <boost/exception/exception.hpp>
#include <boost/exception/diagnostic_information.hpp>
#include <boost/exception_ptr.hpp> 

#include "keto/common/Log.hpp"
#include "keto/common/MetaInfo.hpp"
#include "keto/common/Exception.hpp"
#include "keto/environment/EnvironmentManager.hpp"
#include "keto/environment/Constants.hpp"
#include "keto/module/ModuleManager.hpp"

namespace ketoEnv = keto::environment;
namespace ketoCommon = keto::common;
namespace ketoModule = keto::module;

// the shared ptr for the module manager
std::shared_ptr<ketoModule::ModuleManager> moduleManagerPtr;


boost::program_options::options_description generateOptionDescriptions() {
    boost::program_options::options_description optionDescripion;
    
    optionDescripion.add_options()
            ("help,h", "Print this help message and exit.")
            ("version,v", "Print version information.");
    
    return optionDescripion;
}

void signalHandler(int signal) {
    if (moduleManagerPtr) {
        moduleManagerPtr->terminate();
    }
}


int main(int argc, char** argv)
{
    try {
        // setup the signal handler
        signal(SIGINT, signalHandler);
        
        // setup the environment
        boost::program_options::options_description optionDescription =
                generateOptionDescriptions();
        std::shared_ptr<ketoEnv::EnvironmentManager> manager = 
                ketoEnv::EnvironmentManager::init(
                ketoEnv::Constants::KETOD_CONFIG_FILE,
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
        
        KETO_LOG_INFO << "Instantiate the module manager";
        moduleManagerPtr = ketoModule::ModuleManager::init();
        
        KETO_LOG_INFO << "Load the module";
        moduleManagerPtr->load();
        
        KETO_LOG_INFO << "Monitor the modules";
        moduleManagerPtr->monitor();
        
        KETO_LOG_INFO << "Unload the module";
        moduleManagerPtr->unload();
        
        KETO_LOG_INFO << "KETOD Complete";
        
    } catch (keto::common::Exception& ex) {
        std::cerr << "[keto::common::Exception]Keto exited unexpectedly : " << ex.what() << std::endl;
        std::cerr << "Cause: " << boost::diagnostic_information(ex,true) << std::endl;
        KETO_LOG_ERROR << "Failed to start because : " << ex.what();
        KETO_LOG_ERROR << "Cause: " << boost::diagnostic_information(ex,true);
        // unload to force a clean up
        if (moduleManagerPtr) {
            moduleManagerPtr->unload();
        }
        return -1;
    } catch (boost::exception& ex) {
        std::cerr << "[boost::exception]Keto exited unexpectedly : " << boost::diagnostic_information(ex,true) << std::endl;
        KETO_LOG_ERROR << "Failed to start because : " << boost::diagnostic_information(ex,true);
        // unload to force a clean up
        if (moduleManagerPtr) {
            moduleManagerPtr->unload();
        }
        return -1;
    } catch (std::exception& ex) {
        std::cerr << "[std::exception]Keto exited unexpectedly : " << std::endl;
        std::cerr << "Keto exited unexpectedly : " << ex.what() << std::endl;
        KETO_LOG_ERROR << "Keto exited unexpectedly : " << ex.what();
        // unload to force a clean up
        if (moduleManagerPtr) {
            moduleManagerPtr->unload();
        }
        return -1;
    } catch (...) {
        std::cerr << "[unknown]Keto exited unexpectedly : " << std::endl;
        std::cerr << "Keto exited unexpectedly" << std::endl;
        KETO_LOG_ERROR << "Keto exited unexpectedly.";
        // unload to force a clean up
        if (moduleManagerPtr) {
            moduleManagerPtr->unload();
        }
        return -1;
    }
    KETO_LOG_INFO << "Exit";
}
