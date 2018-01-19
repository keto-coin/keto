/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EventServiceModule.hpp
 * Author: ubuntu
 *
 * Created on January 19, 2018, 7:20 AM
 */

#ifndef EVENTSERVICEMODULE_HPP
#define EVENTSERVICEMODULE_HPP

#include <string>
#include <map>
#include <memory>

#include <boost/signals2.hpp>

#include "keto/event/Event.hpp"
#include "keto/event/EventServiceInterface.hpp"
#include "keto/module/ModuleInterface.hpp"
#include "keto/event/Exception.hpp"

namespace keto {
namespace event {


class EventServiceModule : public keto::module::ModuleInterface, 
        public EventServiceInterface {
public:
    typedef boost::signals2::signal<keto::event::handler> signalHandler;
    typedef std::shared_ptr<signalHandler> Signal;
    
    EventServiceModule();
    EventServiceModule(const EventServiceModule& orig) = delete;
    virtual ~EventServiceModule();
    
    // meta methods
    virtual const std::string getName() const;
    virtual const std::string getDescription() const;
    virtual const std::string getVersion() const;
    
    // process trigger event
    virtual void triggerEvent(const Event& event);
    virtual Event processEvent(const Event& event);
    virtual void registerEventHandler(const std::string& name, handler handlerMethod);
    virtual void deregisterEventHandler(const std::string& name);
    
private:
    std::mutex classMutex;
    std::condition_variable stateCondition;
    std::map<std::string,Signal> registeredSignals;
    
    void addEventHandler(const std::string& name, handler handlerMethod);
    Signal getEventHandler(const std::string& name);
    void removeEventHandler(const std::string& name);
};

}
}

#endif /* EVENTSERVICEMODULE_HPP */

