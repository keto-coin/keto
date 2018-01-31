/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   VersionManagerModuleManager.cpp
 * Author: ubuntu
 * 
 * Created on January 20, 2018, 5:03 PM
 */

#include <boost/dll/alias.hpp>
#include <boost/dll/shared_library.hpp>
#include <boost/shared_ptr.hpp>

#include "keto/common/Log.hpp"
#include "keto/common/MetaInfo.hpp"

#include "keto/version_manager/VersionManagerModuleManager.hpp"

namespace keto {
namespace version_manager {


VersionManagerModuleManager::VersionManagerModuleManager() {
}

VersionManagerModuleManager::~VersionManagerModuleManager() {
}

// meta methods
const std::string VersionManagerModuleManager::getName() const {
    return "VersionManagerModuleManager";
}

const std::string VersionManagerModuleManager::getDescription() const {
    return "The version manager responsible for managing the keto versions running.";
}

const std::string VersionManagerModuleManager::getVersion() const {
    return keto::common::MetaInfo::VERSION;
}

// lifecycle methods
void VersionManagerModuleManager::start() {
    modules["VersionManagerModule"] = std::make_shared<VersionManagerModule>();
    KETO_LOG_INFO << "[VersionManagerModuleManager] Started the VersionManagerModuleManager";
}

void VersionManagerModuleManager::stop() {
    modules.clear();
    KETO_LOG_INFO << "[VersionManagerModuleManager] The VersionManagerModuleManager is being stopped";

}

const std::vector<std::string> VersionManagerModuleManager::listModules() {
    std::vector<std::string> keys;
    std::transform(
        this->modules.begin(),
        this->modules.end(),
        std::back_inserter(keys),
        [](const std::map<std::string,std::shared_ptr<keto::module::ModuleInterface>>::value_type 
            &pair){return pair.first;});
    return keys;
}

const std::shared_ptr<keto::module::ModuleInterface> VersionManagerModuleManager::getModule(const std::string& name) {
    return modules[name];
}

boost::shared_ptr<VersionManagerModuleManager> VersionManagerModuleManager::create_module() {
    return boost::shared_ptr<VersionManagerModuleManager>(new VersionManagerModuleManager());
}

BOOST_DLL_ALIAS(
    keto::version_manager::VersionManagerModuleManager::create_module,
    create_module                               
)


}
}