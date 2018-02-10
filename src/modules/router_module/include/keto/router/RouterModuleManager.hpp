/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RouterModuleManager.hpp
 * Author: ubuntu
 *
 * Created on February 9, 2018, 11:12 AM
 */

#ifndef ROUTERMODULEMANAGER_HPP
#define ROUTERMODULEMANAGER_HPP

#include <string>
#include <map>
#include <memory>

#include "keto/module/ModuleManagementInterface.hpp"
#include "keto/router/RouterModule.hpp"

namespace keto {
namespace router {

class RouterModuleManager : public keto::module::ModuleManagementInterface {
public:
    RouterModuleManager();
    RouterModuleManager(const RouterModuleManager& orig) = delete;
    virtual ~RouterModuleManager();
    
    // meta methods
    virtual const std::string getName() const;
    virtual const std::string getDescription() const;
    virtual const std::string getVersion() const;
    
    // lifecycle methods
    virtual void start();
    virtual void stop();
    
    virtual const std::vector<std::string> listModules();
    virtual const std::shared_ptr<keto::module::ModuleInterface> getModule(const std::string& name);
    
    static boost::shared_ptr<RouterModuleManager> create_module();

private:
    std::map<std::string,std::shared_ptr<keto::module::ModuleInterface>> modules;
    
};


}
}

#endif /* ROUTERMODULEMANAGER_HPP */

