/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SandboxModule.hpp
 * Author: ubuntu
 *
 * Created on January 20, 2018, 4:28 PM
 */

#ifndef SANDBOXMODULE_HPP
#define SANDBOXMODULE_HPP

#include <string>
#include <map>
#include <memory>

#include "keto/module/ModuleInterface.hpp"

namespace keto {
namespace sandbox {


class SandboxModule : public keto::module::ModuleInterface {
public:
    SandboxModule();
    SandboxModule(const SandboxModule& orig) = delete;
    virtual ~SandboxModule();
    
    // meta methods
    virtual const std::string getName() const;
    virtual const std::string getDescription() const;
    virtual const std::string getVersion() const;

private:

};


}
}

#endif /* SANDBOXMODULE_HPP */

