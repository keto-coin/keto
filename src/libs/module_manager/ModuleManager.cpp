/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ModuleManager.cpp
 * Author: ubuntu
 * 
 * Created on January 15, 2018, 3:12 PM
 */

#include <iterator>
#include <vector>
#include <algorithm>
#include <iostream>

#include <boost/filesystem/operations.hpp>
#include <condition_variable>


#include "keto/common/Log.hpp"
#include "keto/environment/EnvironmentManager.hpp"
#include "keto/module/ModuleManager.hpp"
#include "keto/module/Constants.hpp"
#include "keto/module/Exception.hpp"
#include "keto/module/ModuleWrapper.hpp"
#include "keto/module/ModuleManagementInterface.hpp"
#include "include/keto/module/ModuleWrapper.hpp"


namespace keto {
namespace module {
    
namespace ketoEnv = keto::environment;

static std::shared_ptr<ModuleManager> singleton;

ModuleManager::ModuleManager() {
    this->currentState = inited;
    this->moduleDir = ketoEnv::EnvironmentManager::getInstance()->getEnv()->getInstallDir()
            / Constants::KETO_SHARE;
    if (!boost::filesystem::exists(this->moduleDir)) {
        BOOST_THROW_EXCEPTION(ModuleSharedDirException());
    }
    this->tmpDir = ketoEnv::EnvironmentManager::getInstance()->getEnv()->getInstallDir()
            / Constants::KETO_TMP;
    if (!boost::filesystem::exists(this->tmpDir)) {
        if (!boost::filesystem::create_directories(this->tmpDir)) {
            BOOST_THROW_EXCEPTION(ModuleTmpDirException("Failed to create the directory : " +
                this->tmpDir.string()));
        }
    }
}

ModuleManager::~ModuleManager() {
}

std::shared_ptr<ModuleManager>& ModuleManager::init() {
    if (!singleton) {
        singleton = std::shared_ptr<ModuleManager>(new ModuleManager());
    }
    return singleton;
}

std::shared_ptr<ModuleManager>& ModuleManager::getInstance() {
    return singleton;
}

// module lifecycle methods
void ModuleManager::load() {
    // load 
    this->setState(State::loading);
    std::vector<boost::filesystem::path> files;                                // so we can sort them later

    std::copy(boost::filesystem::directory_iterator(this->moduleDir), 
            boost::filesystem::directory_iterator(), std::back_inserter(files));

    std::sort(files.begin(), files.end());
    
    for (std::vector<boost::filesystem::path>::const_iterator it(files.begin()), 
            it_end(files.end()); it != it_end; ++it) {
        load(*it);
    }
    
    for (std::map<boost::filesystem::path,std::shared_ptr<ModuleWrapper>>::iterator it=loadedLibraryModuleManagers.begin(); 
            it!=loadedLibraryModuleManagers.end(); ++it) {
        it->second->getModuleManagerInterface()->postStart();
    }
    
    this->setState(State::loaded);
    
}

void ModuleManager::monitor() {
    
    this->setState(State::monitoring);
    while(this->checkState() != State::terminated) {
        if (this->checkForReload()) {
            this->unload();
            this->load();
            this->setState(State::monitoring);
        }
    }
    
    
}

void ModuleManager::unload() {
    this->setState(State::unloading);
    std::map<boost::filesystem::path,std::shared_ptr<ModuleWrapper>> loadedLibraryModule;
    {
        std::lock_guard<std::mutex> guard(this->classMutex);
        // copy the contents
        loadedLibraryModule = this->loadedLibraryModuleManagers;
        
        
    } 
    
    for (std::map<boost::filesystem::path,std::shared_ptr<ModuleWrapper>>::reverse_iterator it=loadedLibraryModule.rbegin(); 
            it!=loadedLibraryModule.rend(); ++it) {
        it->second->getModuleManagerInterface()->stop();
    }
    
    {
        std::lock_guard<std::mutex> guard(this->classMutex);
        this->loadedModules.clear();
        this->loadedModuleManagementInterfaces.clear();
        this->loadedLibraryModuleManagers.clear();
        
    }
    
    for (std::map<boost::filesystem::path,std::shared_ptr<ModuleWrapper>>::reverse_iterator it=loadedLibraryModule.rbegin(); 
            it!=loadedLibraryModule.rend(); ++it) {
        it->second->unload();
    }
    // clear the modules
    loadedLibraryModule.clear();

    // set the state
    this->setState(State::unloaded);
}


void ModuleManager::terminate() {
    std::unique_lock<std::mutex> uniqueLock(this->classMutex);
    this->currentState = State::terminated;
    this->stateCondition.notify_all();
}



ModuleManager::State ModuleManager::getState() {
    std::lock_guard<std::mutex> guard(this->classMutex);
    return this->currentState;
}

// modules methods
std::vector<std::string> ModuleManager::listModules() {
    std::lock_guard<std::mutex> guard(this->classMutex);
    std::vector<std::string> keys;
    std::transform(
        this->loadedModules.begin(),
        this->loadedModules.end(),
        std::back_inserter(keys),
        [](const std::map<std::string,std::shared_ptr<ModuleInterface>>::value_type &pair)
        {return pair.first;});
    return keys;
}

std::shared_ptr<ModuleInterface> ModuleManager::getModule(
    const std::string& moduleName) {
    std::lock_guard<std::mutex> guard(this->classMutex);
    return this->loadedModules[moduleName];
}


std::vector<std::string> ModuleManager::listModuleManagementInterfaces() {
    std::lock_guard<std::mutex> guard(this->classMutex);
    std::vector<std::string> keys;
    std::transform(
        this->loadedModuleManagementInterfaces.begin(),
        this->loadedModuleManagementInterfaces.end(),
        std::back_inserter(keys),
        [](const std::map<std::string,boost::shared_ptr<ModuleManagementInterface>>::value_type 
            &pair){return pair.first;});
    return keys;
}

boost::shared_ptr<ModuleManagementInterface> ModuleManager::getModuleManagementInterface(
    const std::string& moduleManagement) {
    std::lock_guard<std::mutex> guard(this->classMutex);
    return this->loadedModuleManagementInterfaces[moduleManagement];
}


std::vector<boost::filesystem::path> ModuleManager::listModuleFiles() {
    std::lock_guard<std::mutex> guard(this->classMutex);
    std::vector<boost::filesystem::path> keys;
    std::transform(
        this->loadedLibraryModuleManagers.begin(),
        this->loadedLibraryModuleManagers.end(),
        std::back_inserter(keys),
        [](const std::map<boost::filesystem::path,std::shared_ptr<ModuleWrapper>>::value_type 
            &pair){return pair.first;});
    return keys;
}


std::shared_ptr<ModuleWrapper> ModuleManager::getModuleWrapper(
    const boost::filesystem::path& modulePath) {
    std::lock_guard<std::mutex> guard(this->classMutex);
    return this->loadedLibraryModuleManagers[modulePath];
}


void ModuleManager::load(const boost::filesystem::path& libraryPath) {
    // set the module wrapper ptr at an appropriate point to prevent the
    // library from being unloaded before we can extract the message
    std::shared_ptr<ModuleWrapper> moduleWrapperPtr;
    boost::shared_ptr<ModuleManagementInterface> moduleManagerInterfacePtr;
        
    try {
    
        // setup a module wrapper and load and start the module
        moduleWrapperPtr = std::shared_ptr<ModuleWrapper>(
                new ModuleWrapper(libraryPath,this->tmpDir));
        moduleWrapperPtr->load();
        moduleManagerInterfacePtr = 
                moduleWrapperPtr->getModuleManagerInterface();
        moduleManagerInterfacePtr->start();

        // add the module to the cointainers
        std::lock_guard<std::mutex> guard(this->classMutex);
        this->loadedLibraryModuleManagers[libraryPath] = moduleWrapperPtr;
        this->loadedModuleManagementInterfaces[moduleWrapperPtr->getModuleManagerInterface()->getName()] = 
                moduleWrapperPtr->getModuleManagerInterface();
        std::vector<std::string> modules = moduleWrapperPtr->getModuleManagerInterface()->listModules();
        for (std::string name : modules) {
            this->loadedModules[name] = 
                    moduleWrapperPtr->getModuleManagerInterface()->getModule(name);
        }
    
    } catch (keto::common::Exception& ex) {
        if (moduleManagerInterfacePtr) {
            moduleManagerInterfacePtr->stop();
        }
        std::stringstream ss;
        ss << "Failed to load the module [" << libraryPath.string() << "] : " << ex.what() << std::endl;
        ss << "Cause: " << boost::diagnostic_information(ex,true) << std::endl;
        BOOST_THROW_EXCEPTION(keto::module::ModuleLoadException(
                ss.str()));
    } catch (boost::exception& ex) {
        // attempt to clear up
        if (moduleManagerInterfacePtr) {
            moduleManagerInterfacePtr->stop();
        }
        std::stringstream ss;
        ss << "Failed to load the module [" << libraryPath.string() << "] : " 
                << boost::diagnostic_information(ex,true) << std::endl;
        BOOST_THROW_EXCEPTION(keto::module::ModuleLoadException(
                ss.str()));
    } catch (std::exception& ex) {
        // attempt to clear up
        if (moduleManagerInterfacePtr) {
            moduleManagerInterfacePtr->stop();
        }
        std::stringstream ss;
        ss << "Failed to load the module [" << libraryPath.string() << "] : " << ex.what() << std::endl;
        BOOST_THROW_EXCEPTION(keto::module::ModuleLoadException(
                ss.str()));
    } catch (...) {
        // attempt to clear up
        if (moduleManagerInterfacePtr) {
            moduleManagerInterfacePtr->stop();
        }
        std::stringstream ss;
        ss << "Failed to load the module [" << libraryPath.string() << "]" << std::endl;
        BOOST_THROW_EXCEPTION(keto::module::ModuleLoadException(
                ss.str()));
    }
}


bool ModuleManager::checkForReload() {
    
    std::map<boost::filesystem::path,std::shared_ptr<ModuleWrapper>> loadedLibraryModuleManagers;
    {
        std::lock_guard<std::mutex> guard(this->classMutex);
        // copy the contents
        loadedLibraryModuleManagers = this->loadedLibraryModuleManagers;
    }
    for (std::map<boost::filesystem::path,std::shared_ptr<ModuleWrapper>>::iterator it=loadedLibraryModuleManagers.begin(); 
            it!=loadedLibraryModuleManagers.end(); ++it) {
        if (it->second->requireReload()) {
            return true;
        }
    }
    return false;
}

ModuleManager::State ModuleManager::checkState() {
    std::unique_lock<std::mutex> uniqueLock(this->classMutex);
    KETO_LOG_DEBUG << "Before check state";
    this->stateCondition.wait_for(uniqueLock,std::chrono::milliseconds(60 * 1000));
    KETO_LOG_DEBUG << "After check state";
    return this->currentState;
}

void ModuleManager::setState(const ModuleManager::State& state) {
    std::lock_guard<std::mutex> guard(this->classMutex);
    if (this->currentState == State::terminated) {
        return;
    }
    this->currentState = state;
}

}
}