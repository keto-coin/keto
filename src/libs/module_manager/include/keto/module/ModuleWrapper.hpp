/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ModuleWrapper.hpp
 * Author: Brett Chaldecott
 *
 * Created on January 15, 2018, 6:44 PM
 */

#ifndef MODULEWRAPPER_HPP
#define MODULEWRAPPER_HPP

#include <string>
#include <memory>

// boost includes
#include <boost/dll/shared_library.hpp>
#include <boost/shared_ptr.hpp>

namespace keto {
namespace module {



class ModuleWrapper {
public:
    // enable the module manager to access the protected member variables
    friend class ModuleManager;
    
    ModuleWrapper(const ModuleWrapper& orig) = delete;
    virtual ~ModuleWrapper();
    
    // get the module interface
    const boost::filesystem::path& getSourcePath() const;
    const boost::filesystem::path& getLoadPath() const;
    const std::time_t& getLastTouchTime() const;
    boost::shared_ptr<ModuleManagementInterface>& getModuleManagerInterface();
    
protected:
    ModuleWrapper(boost::filesystem::path sourcePath,
            boost::filesystem::path tmpDir);
    
    // the load and unload
    void load();
    void unload();
    bool requireReload();
    
private:
    boost::dll::shared_library sharedLibrary;
    boost::filesystem::path sourcePath;
    boost::filesystem::path loadPath;
    std::time_t lastTouchTime;
    
    boost::shared_ptr<ModuleManagementInterface> moduleManagementInterfacePtr;
    std::shared_ptr<boost::dll::shared_library> sharedLibrary;
};

}
}

#endif /* MODULEWRAPPER_HPP */

