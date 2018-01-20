/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   KeystoreModuleManager.hpp
 * Author: ubuntu
 *
 * Created on January 20, 2018, 4:40 PM
 */

#ifndef KEYSTOREMODULEMANAGER_HPP
#define KEYSTOREMODULEMANAGER_HPP

#include <string>
#include <map>
#include <memory>

#include "keto/module/ModuleManagementInterface.hpp"
#include "keto/keystore/KeystoreModule.hpp"


namespace keto {
namespace keystore {

class KeystoreModuleManager : public keto::module::ModuleManagementInterface {
public:
    KeystoreModuleManager();
    KeystoreModuleManager(const KeystoreModuleManager& orig) = delete;
    virtual ~KeystoreModuleManager();
    
    // meta methods
    virtual const std::string getName() const;
    virtual const std::string getDescription() const;
    virtual const std::string getVersion() const;
    
    // lifecycle methods
    virtual void start();
    virtual void stop();
    
    virtual const std::vector<std::string> listModules();
    virtual const std::shared_ptr<keto::module::ModuleInterface> getModule(const std::string& name);
    
    static boost::shared_ptr<KeystoreModuleManager> create_module();

private:
    std::map<std::string,std::shared_ptr<keto::module::ModuleInterface>> modules;

};


}
}


#endif /* KEYSTOREMODULEMANAGER_HPP */

