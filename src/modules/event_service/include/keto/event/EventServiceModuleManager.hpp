/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EventServiceModuleManager.hpp
 * Author: ubuntu
 *
 * Created on January 18, 2018, 2:47 PM
 */

#ifndef EVENTSERVICEMODULEMANAGER_HPP
#define EVENTSERVICEMODULEMANAGER_HPP

#include "keto/event/EventServiceInterface.hpp"
#include "keto/module/ModuleManagementInterface.hpp"

namespace keto {
namespace event {
        

class EventServiceModuleManager : public keto::module::ModuleManagementInterface  {
public:
    EventServiceModuleManager();
    EventServiceModuleManager(const EventServiceModuleManager& orig) = delete;
    virtual ~EventServiceModuleManager();
    
    // meta methods
    virtual const std::string getName() const;
    virtual const std::string getDescription() const;
    virtual const std::string getVersion() const;
    
    // lifecycle methods
    virtual void start();
    virtual void stop();
    
    virtual const std::vector<std::string> listModules();
    virtual const std::shared_ptr<keto::module::ModuleInterface> getModule(const std::string& name);
    
    static boost::shared_ptr<EventServiceModuleManager> create_module();
    
private:
    std::map<std::string,std::shared_ptr<keto::module::ModuleInterface>> modules;
};


    
}
}

#endif /* EVENTSERVICEMODULEMANAGER_HPP */

