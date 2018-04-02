/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BlockModuleManager.hpp
 * Author: Brett Chaldecott
 *
 * Created on February 10, 2018, 3:34 PM
 */

#ifndef BLOCKMODULEMANAGER_HPP
#define BLOCKMODULEMANAGER_HPP

#include <string>
#include <map>
#include <memory>

#include "keto/module/ModuleManagementInterface.hpp"
#include "keto/block/BlockModule.hpp"

namespace keto {
namespace block {


class BlockModuleManager : public keto::module::ModuleManagementInterface {
public:
    BlockModuleManager();
    BlockModuleManager(const BlockModuleManager& orig) = delete;
    virtual ~BlockModuleManager();
    
    // meta methods
    virtual const std::string getName() const;
    virtual const std::string getDescription() const;
    virtual const std::string getVersion() const;
    
    // lifecycle methods
    virtual void start();
    virtual void postStart();
    virtual void stop();
    
    virtual const std::vector<std::string> listModules();
    virtual const std::shared_ptr<keto::module::ModuleInterface> getModule(const std::string& name);
    
    static boost::shared_ptr<BlockModuleManager> create_module();

private:
    
    std::map<std::string,std::shared_ptr<keto::module::ModuleInterface>> modules;
    

};

}
}

#endif /* BLOCKMODULEMANAGER_HPP */

