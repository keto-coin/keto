/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ModuleManager.h
 * Author: Brett Chaldecott
 *
 * Created on January 15, 2018, 3:12 PM
 */

#ifndef MODULEMANAGER_H
#define MODULEMANAGER_H

#include <memory>
#include <string>
#include <set>
#include <map>
#include <mutex>
#include <condition_variable>

#include "keto/module/ModuleManagementInterface.hpp"
#include "keto/module/ModuleWrapper.hpp"

namespace keto {
namespace module {
    

/**
 * The module manager is responsible for managing and dynamically loading modules.
 */
class ModuleManager {
public:
    /**
     * The state enum containing the various states that the module manager can
     * be in.
     */
    enum State {
        inited,
        loading,
        loaded,
        unloading,
        unloaded,
        monitoring,
        terminated
    };
    
    /**
     * Delete the module manager copy constructor to prevent it from being used.
     * @param orig
     */
    ModuleManager(const ModuleManager& orig) = delete;
    
    /**
     * The virtual destructor
     */
    virtual ~ModuleManager();
    
    // singleton methods
    /**
     * The singleton method to init the module manager.
     * 
     * @return The reference to the module manager singleton.
     */
    static std::shared_ptr<ModuleManager>& init();
    
    /**
     * The singleton method that returns an instance of the module manager.
     * 
     * @return The reference to the module manager
     */
    static std::shared_ptr<ModuleManager>& getInstance();
    
    // module lifecycle methods
    void load();
    void monitor();
    void unload();
    
    /**
     * This method is called to terminate the module manager. This will result in
     * a complete stop of all loaded modules and an unload.
     * 
     * @param state
     */
    void terminate();
    
    
    // modules methods
    /**
     * This method returns the current state of the module manager.
     * 
     * @return The current state of the module manager
     */
    State getState();
    
    
    /**
     * Get the list of modules that have been loaded.
     * 
     * @return The list of modules that have been loaded.
     */
    std::vector<std::string> listModules();
    
    
    /**
     * This method gets the module identified by the name.
     * 
     * @param moduleName The name of the module to retrieve.
     * @return The reference to the loaded module.
     */
    std::shared_ptr<ModuleInterface> getModule(const std::string& moduleName);
    
    
    /**
     * Get the list of module management interfaces
     * 
     * @return The list of loaded module management interfaces
     */
    std::vector<std::string> listModuleManagementInterfaces();
    
    
    /**
     * This method returns a reference to the module management interface.
     * 
     * @param moduleManagement
     * 
     * @return The reference to the module management interface
     */
    boost::shared_ptr<ModuleManagementInterface> getModuleManagementInterface(const std::string& moduleManagement);
    
    
    /**
     * This method returns a list of all the dynamic objects that have been loaded.
     * 
     * @return The list of files that have been loaded.
     */
    std::vector<boost::filesystem::path> listModuleFiles();
    
    
    /**
     * This method returns a reference to the module manager interface
     * 
     * @param modulePath The path to the module manager
     * @return The smart pointer to the module manager
     */
    std::shared_ptr<ModuleWrapper> getModuleWrapper(const boost::filesystem::path& modulePath);
    
    
    
private:
    // private member variables.
    State currentState;
    boost::filesystem::path moduleDir;
    boost::filesystem::path tmpDir;
    std::mutex classMutex;
    std::condition_variable stateCondition;
    std::map<std::string,std::shared_ptr<ModuleInterface>> loadedModules;
    std::map<std::string,boost::shared_ptr<ModuleManagementInterface>> loadedModuleManagementInterfaces;
    std::map<boost::filesystem::path,std::shared_ptr<ModuleWrapper>> loadedLibraryModuleManagers;
    
    /**
     * Private constructor to prevent anyone from creating a new instance
     */
    ModuleManager();
    
    /**
     * This method is responsible for loading the entries
     * @param library
     */
    void load(const boost::filesystem::path& library);
    
    /**
     * This method 
     */
    bool checkForReload();
    
    /**
     * This method is called to check the state
     * 
     * @return The state of the object.
     */
    State checkState();
    
    /**
     * The thread safe method to set the state
     * @param state
     */
    void setState(const State& state);
};

    
}
}

#endif /* MODULEMANAGER_H */

