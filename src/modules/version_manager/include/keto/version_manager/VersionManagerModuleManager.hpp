/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   VersionManagerModuleManager.hpp
 * Author: ubuntu
 *
 * Created on January 20, 2018, 5:03 PM
 */

#ifndef VERSIONMANAGERMODULEMANAGER_HPP
#define VERSIONMANAGERMODULEMANAGER_HPP

#include <string>
#include <map>
#include <memory>

#include "keto/module/ModuleManagementInterface.hpp"
#include "keto/version_manager/VersionManagerModule.hpp"


namespace keto {
namespace version_manager {

class VersionManagerModuleManager : public keto::module::ModuleManagementInterface {
public:
    VersionManagerModuleManager();
    VersionManagerModuleManager(const VersionManagerModuleManager& orig) = delete;
    virtual ~VersionManagerModuleManager();
    
    // meta methods
    virtual const std::string getName() const;
    virtual const std::string getDescription() const;
    virtual const std::string getVersion() const;
    
    // lifecycle methods
    virtual void start();
    virtual void stop();
    
    virtual const std::vector<std::string> listModules();
    virtual const std::shared_ptr<keto::module::ModuleInterface> getModule(const std::string& name);
    
    static boost::shared_ptr<VersionManagerModuleManager> create_module();

private:
    std::map<std::string,std::shared_ptr<keto::module::ModuleInterface>> modules;

};


}
}

#endif /* VERSIONMANAGERMODULEMANAGER_HPP */

