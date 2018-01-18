/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ModuleWrapper.cpp
 * Author: ubuntu
 * 
 * Created on January 15, 2018, 6:44 PM
 */

#include <boost/filesystem/operations.hpp>
#include <boost/dll/import.hpp> // for import_alias
#include <boost/function.hpp>

#include "keto/module/ModuleWrapper.hpp"

namespace keto {
namespace module {

ModuleWrapper::ModuleWrapper(boost::filesystem::path sourcePath,
            boost::filesystem::path tmpDir) : sourcePath(sourcePath) {
    this->loadPath = boost::filesystem::unique_path(tmpDir / "%%%%-%%%%-%%%%-%%%%.so");
    this->lastTouchTime = boost::filesystem::last_write_time(this->sourcePath);
    boost::filesystem::copy_file(this->sourcePath,this->loadPath);
    this->sharedLibrary = boost::dll::shared_library(this->loadPath);
}

ModuleWrapper::~ModuleWrapper() {
}

const boost::filesystem::path& ModuleWrapper::getSourcePath() const {
    return this->sourcePath;
}

const boost::filesystem::path& ModuleWrapper::getLoadPath() const {
    return this->loadPath;
}


const std::time_t& ModuleWrapper::getLastTouchTime() const {
    return this->lastTouchTime;
}

boost::shared_ptr<ModuleManagementInterface>& ModuleWrapper::getModuleManagerInterface() {
    return this->moduleManagementInterfacePtr;
}


// the load and unload
void ModuleWrapper::load() {
    typedef boost::shared_ptr<ModuleManagementInterface> (module_create_t)();
    boost::function<module_create_t> creator;

    creator = boost::dll::import_alias<module_create_t>(             // type of imported symbol must be explicitly specified
        this->sharedLibrary,                                            // path to library
        "create_module"                              // do append extensions and prefixes
    );

    this->moduleManagementInterfacePtr = creator();
}


void ModuleWrapper::unload() {
    this->moduleManagementInterfacePtr.reset();
    this->sharedLibrary.unload();
}


bool ModuleWrapper::requireReload() {
    // check if the source file still exists
    if (!boost::filesystem::exists(this->sourcePath)) {
        return true;
    }
    
    // check if the file has been modified thus requiring a reload.
    return (boost::filesystem::last_write_time(this->sourcePath) != this->lastTouchTime);
}


}
}