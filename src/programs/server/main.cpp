
#include <iostream>
#include <boost/exception/exception.hpp>
#include <boost/exception/diagnostic_information.hpp>
#include <boost/exception_ptr.hpp> 

#include "keto/common/Log.hpp"
#include "keto/common/Exception.hpp"
#include "keto/environment/EnvironmentManager.hpp"
#include "keto/environment/Constants.hpp"


boost::program_options::options_description generateOptionDescriptions() {
    boost::program_options::options_description optionDescripion;
    
    return optionDescripion;
}

int main(int argc, char** argv)
{
    try {
        keto::environment::EnvironmentManager::init(keto::environment::Constants::KETOD_CONFIG_FILE,
                generateOptionDescriptions(),argc,argv);

        KETO_LOG_INFO << "KETOD Executed";
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
