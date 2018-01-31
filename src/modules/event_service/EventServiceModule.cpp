/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EventServiceModule.cpp
 * Author: ubuntu
 * 
 * Created on January 19, 2018, 7:20 AM
 */

#include <condition_variable>
#include <boost/optional/optional.hpp>

#include "keto/event/EventServiceModule.hpp"
#include "keto/common/MetaInfo.hpp"

namespace keto {
namespace event {


EventServiceModule::EventServiceModule() {
}

EventServiceModule::~EventServiceModule() {
}

const std::string EventServiceModule::getName() const {
    return "EventService";
}

const std::string EventServiceModule::getDescription() const {
    return "Event Service Description";
}

const std::string EventServiceModule::getVersion() const {
    return keto::common::MetaInfo::VERSION;
}
    

void EventServiceModule::triggerEvent(const Event& event) {
    EventServiceModule::Signal signal =this->getEventHandler(event.getName());
            
    (*signal.get())(event);
}


Event EventServiceModule::processEvent(const Event& event) {
    EventServiceModule::Signal signal =this->getEventHandler(event.getName());
    boost::optional<Event> option = (*signal.get())(event);
    return option.get();
}


void EventServiceModule::registerEventHandler(const std::string& name, handler handlerMethod) {
    this->addEventHandler(name,handlerMethod);
}

void EventServiceModule::deregisterEventHandler(const std::string& name) {
    this->removeEventHandler(name);
}

void EventServiceModule::addEventHandler(const std::string& name, keto::event::handler handlerMethod) {
    Signal signal = std::make_shared<boost::signals2::signal<keto::event::handler>>();
    signal->connect(handlerMethod);
    std::lock_guard<std::mutex> guard(this->classMutex);
    if (this->registeredSignals.count(name)) {
        BOOST_THROW_EXCEPTION(DuplicateEventHandlerException(
                "Pre-existing event handler by the name of : " +
                name));
    }
    this->registeredSignals[name] = signal;
}

EventServiceModule::Signal EventServiceModule::getEventHandler(const std::string& name) {
    std::lock_guard<std::mutex> guard(this->classMutex);
    if (!this->registeredSignals.count(name)) {
        BOOST_THROW_EXCEPTION(UnknownEventHandlerException("Unknown event handler : " +
                name));
    }
    return this->registeredSignals[name];
}

void EventServiceModule::removeEventHandler(const std::string& name) {
    std::lock_guard<std::mutex> guard(this->classMutex);
    this->registeredSignals.erase(name);
}

}
}