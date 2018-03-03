/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EventRegistry.hpp
 * Author: ubuntu
 *
 * Created on March 3, 2018, 10:25 AM
 */

#ifndef KETO_ROUTER_EVENTREGISTRY_HPP
#define KETO_ROUTER_EVENTREGISTRY_HPP

#include "keto/event/Event.hpp"

namespace keto {
namespace router {

class EventRegistry {
public:
    EventRegistry(const EventRegistry& orig) = delete;
    virtual ~EventRegistry();
    
    static keto::event::Event routeMessage(const keto::event::Event& event);
    
    static void registerEventHandlers();
    static void deregisterEventHandlers();
private:
    EventRegistry();

};

        
}
}

#endif /* EVENTREGISTRY_HPP */

