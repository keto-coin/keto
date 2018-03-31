/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BalancerModuleManager.hpp
 * Author: ubuntu
 *
 * Created on February 10, 2018, 1:37 PM
 */

#ifndef BALANCERMODULEMANAGER_HPP
#define BALANCERMODULEMANAGER_HPP

#include <string>
#include <map>
#include <memory>

#include "keto/module/ModuleManagementInterface.hpp"
#include "keto/balancer/BalancerModule.hpp"


namespace keto {
namespace balancer {


class BalancerModuleManager : public keto::module::ModuleManagementInterface {
public:
    BalancerModuleManager();
    BalancerModuleManager(const BalancerModuleManager& orig) = delete;
    virtual ~BalancerModuleManager();
    
    // meta methods
    virtual const std::string getName() const;
    virtual const std::string getDescription() const;
    virtual const std::string getVersion() const;
    
    // lifecycle methods
    virtual void start();
    virtual void stop();
    virtual void postStart();
    
    virtual const std::vector<std::string> listModules();
    virtual const std::shared_ptr<keto::module::ModuleInterface> getModule(const std::string& name);
    
    static boost::shared_ptr<BalancerModuleManager> create_module();

private:
    std::map<std::string,std::shared_ptr<keto::module::ModuleInterface>> modules;
    
};


}
}

#endif /* BALANCERMODULEMANAGER_HPP */

