/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestModuleManager.cpp
 * Author: ubuntu
 * 
 * Created on January 18, 2018, 9:30 AM
 */

#include <map>

#include <boost/dll/alias.hpp>
#include <boost/dll/shared_library.hpp>
#include <boost/shared_ptr.hpp>

#include "keto/test/TestModuleManager.hpp"
#include "keto/common/MetaInfo.hpp"
#include "keto/common/Log.hpp"

#include "include/keto/test/TestModuleManager.hpp"

namespace keto {
namespace test {

TestModuleManager::TestModuleManager() {
    KETO_LOG_INFO << "The test module manager has been loaded";
}

TestModuleManager::~TestModuleManager() {
    KETO_LOG_INFO << "The test module manager has been unloaded";
}

// meta methods
const std::string TestModuleManager::getName() const {
    return "TestModuleManager";
}
const std::string TestModuleManager::getDescription() const {
    return "The test module manager for KETO";
}

const std::string TestModuleManager::getVersion() const {
    return keto::common::MetaInfo::VERSION;
}

// lifecycle methods
void TestModuleManager::start() {
    KETO_LOG_INFO << "Start has been called on the test module manager";
    modules["test_module"] = std::make_shared<TestModule>();
}

void TestModuleManager::stop() {
    KETO_LOG_INFO << "Stop has been called on the test module manager";
    modules.clear();
    KETO_LOG_INFO << "The test module has been stopped";
    
}

const std::vector<std::string> TestModuleManager::listModules() {
    std::vector<std::string> keys;
    std::transform(
        this->modules.begin(),
        this->modules.end(),
        std::back_inserter(keys),
        [](const std::map<std::string,std::shared_ptr<keto::module::ModuleInterface>>::value_type 
            &pair){return pair.first;});
    return keys;
}

const std::shared_ptr<keto::module::ModuleInterface>
    TestModuleManager::getModule(const std::string& name) {
    return modules[name];
}

boost::shared_ptr<TestModuleManager> TestModuleManager::create_module() {
    return boost::shared_ptr<TestModuleManager>(new TestModuleManager());
}

BOOST_DLL_ALIAS(
    keto::test::TestModuleManager::create_module,
    create_module                               
)

}
}