/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ModuleInterface.hpp
 * Author: ubuntu
 *
 * Created on January 15, 2018, 3:20 PM
 */

#ifndef MODULE_MANAGEMENT_INTERFACE_HPP
#define MODULE_MANAGEMENT_INTERFACE_HPP

#include <string>
#include <vector>
#include <memory>

#include "keto/module/ModuleInterface.hpp"


namespace keto {
namespace module {

class ModuleManagementInterface {
public:
    friend class ModuleManager;

    // meta methods
    virtual const std::string getName() const = 0;
    virtual const std::string getDescription() const = 0;
    virtual const std::string getVersion() const = 0;
    
    
protected:
    
    // lifecycle methods
    virtual void start() = 0;
    virtual void stop() = 0;
    
    virtual const std::vector<std::string> listModules() = 0;
    virtual const std::shared_ptr<ModuleInterface> getModule(const std::string& name) = 0;
    
};
    
}
}

#endif /* MODULEINTERFACE_HPP */

