/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EventServiceInterface.hpp
 * Author: Brett Chaldecott
 *
 * Created on January 18, 2018, 12:07 PM
 */

#ifndef EVENTSERVICEINTERFACE_HPP
#define EVENTSERVICEINTERFACE_HPP

#include <string>
#include <memory>

#include <keto/module/ModuleManager.hpp>
#include <keto/module/ModuleInterface.hpp>
#include <keto/event/Event.hpp>

namespace keto {
namespace event {

typedef Event (handler)(const Event&);
    
class EventServiceInterface {
public:
    static constexpr const char* KETO_EVENT_SERVICE_MODULE = "event_service";
    
    virtual void triggerEvent(const Event& event) = 0;
    virtual Event processEvent(const Event& event) = 0;
    virtual void registerEventHandler(const std::string& name, handler handlerMethod) = 0;
    virtual void deregisterEventHandler(const std::string& name) = 0;
};

#define TRIGGER_EVENT (event) \
    dynamic_pointer_cast<EventServiceInterface>(std::keto::module::ModuleManager::getInstance()->getModule(EventServiceInterface::KETO_EVENT_SERVICE_MODULE))->triggerEvent(event);

#define PROCESS_EVENT (event) \
    dynamic_pointer_cast<EventServiceInterface>(std::keto::module::ModuleManager::getInstance()->getModule(EventServiceInterface::KETO_EVENT_SERVICE_MODULE))->processEvent(event);

#define REGISTER_EVENT_HANDLER (name,handlerMethod) \
    dynamic_pointer_cast<EventServiceInterface>(std::keto::module::ModuleManager::getInstance()->getModule(EventServiceInterface::KETO_EVENT_SERVICE_MODULE))->registerEventHandler(name,handlerMethod);

#define DE_REGISTER_EVENT_HANDER (name) \
    dynamic_pointer_cast<EventServiceInterface>(std::keto::module::ModuleManager::getInstance()->getModule(EventServiceInterface::KETO_EVENT_SERVICE_MODULE))->deregisterEventHandler(name);


}
}


#endif /* EVENTSERVICEINTERFACE_HPP */

