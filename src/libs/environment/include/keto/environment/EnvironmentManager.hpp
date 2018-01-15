
/* 
 * File:   EnvironmentManager.h
 * Author: Brett Chaldecott
 *
 * Created on January 10, 2018, 12:15 PM
 */

#ifndef ENVIRONMENTMANAGER_H
#define ENVIRONMENTMANAGER_H

// std imports
#include <memory>
#include <string>

// boost imports
#include <boost/program_options/options_description.hpp>

// keto imports
#include "keto/environment/Env.hpp"
#include "keto/environment/Config.hpp"
#include "keto/environment/LogManager.hpp"

namespace po = boost::program_options;


namespace keto {
namespace environment {
    
/**
 * The environment manager
 */
class EnvironmentManager {
public:
    EnvironmentManager(const std::string& config,
        const po::options_description& optionDescription,
        int argc, char** argv);
    EnvironmentManager(const EnvironmentManager& orig) = delete;
    virtual ~EnvironmentManager();
    
    static std::shared_ptr<EnvironmentManager> init(
        const std::string& config,
        const po::options_description& optionDescription,
        int argc, char** argv);
    static std::shared_ptr<EnvironmentManager> getInstance();
    
    
    std::shared_ptr<Env> getEnv();
    
    std::shared_ptr<Config> getConfig();
    
    std::shared_ptr<LogManager> getLogManager();
    
private:
    
    
    
    std::shared_ptr<Env> envPtr;
    std::shared_ptr<Config> configPtr;
    std::shared_ptr<LogManager> logManagerPtr;
    
    
};

}
}

#endif /* ENVIRONMENTMANAGER_H */

