/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Log.cpp
 * Author: ubuntu
 * 
 * Created on January 13, 2018, 6:15 PM
 */

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>

#include "keto/environment/LogManager.hpp"
#include "include/keto/environment/Constants.hpp"

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;

namespace keto {
    namespace environment {
    
LogManager::LogManager(
    const std::shared_ptr<Env>& envPtr,
    const std::shared_ptr<Config>& configPtr) : 
    envPtr(envPtr),configPtr(configPtr) {
    
    boost::filesystem::path logPath = this->envPtr->getInstallDir() + "/"  + Constants::KETO_LOG_DIR; 
    
    if (configPtr->getVariablesMap().count(Constants::KETO_LOG_FILE)) {
        std::string logFile = logPath.string() + "/" + 
                configPtr->getVariablesMap()[Constants::KETO_LOG_FILE].as<std::string>();
        logging::add_file_log
        (
            keywords::file_name = logFile.c_str(),
            keywords::rotation_size = 10 * 1024 * 1024,
            keywords::open_mode = std::ios_base::app,
            keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0),
            keywords::auto_flush = true
        );

    }
    
    boost::log::trivial::severity_level logLevel =
        configPtr->getVariablesMap()[Constants::KETO_LOG_LEVEL].as<boost::log::trivial::severity_level>();
    
    logging::core::get()->set_filter
    (
        logging::trivial::severity >= logLevel
    );
}

LogManager::~LogManager() {
}

    
    }
}
