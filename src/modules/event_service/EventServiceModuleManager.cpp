/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EventServiceModuleManager.cpp
 * Author: ubuntu
 * 
 * Created on January 18, 2018, 2:47 PM
 */

#include <boost/dll/alias.hpp>
#include <boost/dll/shared_library.hpp>
#include <boost/shared_ptr.hpp>

#include "keto/event/EventServiceModuleManager.hpp"
#include "keto/event/EventServiceModule.hpp"

#include "keto/common/Log.hpp"


namespace keto {
namespace event {
        

EventServiceModuleManager::EventServiceModuleManager() {
}

EventServiceModuleManager::~EventServiceModuleManager() {
}

// meta methods
const std::string EventServiceModuleManager::getName() const {
    return "EventServiceModuleManager";
}
const std::string EventServiceModuleManager::getDescription() const {
    return "The event service manager for KETO";
}

const std::string EventServiceModuleManager::getVersion() const {
    return "0.1.0";
}

// lifecycle methods
void EventServiceModuleManager::start() {
    modules[keto::event::EventServiceInterface::KETO_EVENT_SERVICE_MODULE] = 
            std::make_shared<EventServiceModule>();
    KETO_LOG_INFO << "[EventService] The event service has been started";
    
}

void EventServiceModuleManager::stop() {
    modules.clear();
    KETO_LOG_INFO << "[EventService] The event service is being stopped";
}

const std::vector<std::string> EventServiceModuleManager::listModules() {
    std::vector<std::string> keys;
    std::transform(
        this->modules.begin(),
        this->modules.end(),
        std::back_inserter(keys),
        [](const std::map<std::string,std::shared_ptr<keto::module::ModuleInterface>>::value_type 
            &pair){return pair.first;});
    return keys;
}

const std::shared_ptr<keto::module::ModuleInterface>
    EventServiceModuleManager::getModule(const std::string& name) {
    return modules[name];
}

boost::shared_ptr<EventServiceModuleManager> EventServiceModuleManager::create_module() {
    return boost::shared_ptr<EventServiceModuleManager>(new EventServiceModuleManager());
}

BOOST_DLL_ALIAS(
    keto::event::EventServiceModuleManager::create_module,
    create_module                               
)
        
}
}
