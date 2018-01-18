/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestModuleManager.hpp
 * Author: ubuntu
 *
 * Created on January 18, 2018, 9:30 AM
 */

#ifndef TESTMODULEMANAGER_HPP
#define TESTMODULEMANAGER_HPP

#include "keto/module/ModuleManagementInterface.hpp"
#include "keto/module/ModuleInterface.hpp"

#include "keto/test/TestModule.hpp"

namespace keto {
namespace test {
        

class TestModuleManager : public keto::module::ModuleManagementInterface {
public:
    TestModuleManager();
    TestModuleManager(const TestModuleManager& orig) = delete;
    virtual ~TestModuleManager();
    
    // meta methods
    virtual const std::string getName() const;
    virtual const std::string getDescription() const;
    virtual const std::string getVersion() const;
    
    // lifecycle methods
    virtual void start();
    virtual void stop();
    
    virtual const std::vector<std::string> listModules();
    virtual const std::shared_ptr<keto::module::ModuleInterface> getModule(const std::string& name);
    
    static boost::shared_ptr<TestModuleManager> create_module();
    
private:
    std::map<std::string,std::shared_ptr<keto::module::ModuleInterface>> modules;
};


}
}

#endif /* TESTMODULEMANAGER_HPP */

