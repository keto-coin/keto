/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HttpModuleManager.cpp
 * Author: ubuntu
 * 
 * Created on January 20, 2018, 12:32 PM
 */

#include <boost/dll/alias.hpp>
#include <boost/dll/shared_library.hpp>
#include <boost/shared_ptr.hpp>

#include "keto/common/Log.hpp"
#include "keto/http/HttpdModuleManager.hpp"
#include "include/keto/http/HttpdServer.hpp"
#include "keto/common/MetaInfo.hpp"


namespace keto {
namespace http {


HttpdModuleManager::HttpdModuleManager() {
    this->httpServer = std::make_shared<HttpdServer>();
}

HttpdModuleManager::~HttpdModuleManager() {
}

const std::string HttpdModuleManager::getName() const {
    return "HttpdModuleManager";
}

const std::string HttpdModuleManager::getDescription() const {
    return "The implementation of the httpd module manager";
}

const std::string HttpdModuleManager::getVersion() const {
    return keto::common::MetaInfo::VERSION;
}
    
// lifecycle methods
void HttpdModuleManager::start() {
    modules["HttpdModuleManager"] = std::make_shared<HttpdModule>();
    this->httpServer->start();
    KETO_LOG_INFO << "[HttpdModuleManager] Started the HttpdModuleManager";

}
void HttpdModuleManager::stop() {
    this->httpServer->stop();
    modules.clear();
    KETO_LOG_INFO << "[HttpdModuleManager] The HttpdModuleManager is being stopped";
}
    
const std::vector<std::string> HttpdModuleManager::listModules() {
    std::vector<std::string> keys;
    std::transform(
        this->modules.begin(),
        this->modules.end(),
        std::back_inserter(keys),
        [](const std::map<std::string,std::shared_ptr<keto::module::ModuleInterface>>::value_type 
            &pair){return pair.first;});
    return keys;
}

const std::shared_ptr<keto::module::ModuleInterface> HttpdModuleManager::getModule(const std::string& name) {
    return modules[name];
}
    
boost::shared_ptr<HttpdModuleManager> HttpdModuleManager::create_module() {
    return boost::shared_ptr<HttpdModuleManager>(new HttpdModuleManager());
}


BOOST_DLL_ALIAS(
    keto::http::HttpdModuleManager::create_module,
    create_module                               
)

}
}