/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   VersionManagerModule.hpp
 * Author: ubuntu
 *
 * Created on January 20, 2018, 5:03 PM
 */

#ifndef VERSIONMANAGERMODULE_HPP
#define VERSIONMANAGERMODULE_HPP

#include <string>
#include <map>
#include <memory>

#include "keto/module/ModuleInterface.hpp"

namespace keto {
namespace version_manager {

class VersionManagerModule : public keto::module::ModuleInterface {
public:
    VersionManagerModule();
    VersionManagerModule(const VersionManagerModule& orig) = delete;
    virtual ~VersionManagerModule();
    
    // meta methods
    virtual const std::string getName() const;
    virtual const std::string getDescription() const;
    virtual const std::string getVersion() const;
private:

};


}
}

#endif /* VERSIONMANAGERMODULE_HPP */

