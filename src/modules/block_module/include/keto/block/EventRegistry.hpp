/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EventRegistry.hpp
 * Author: ubuntu
 *
 * Created on March 8, 2018, 3:15 AM
 */

#ifndef EVENTREGISTRY_HPP
#define EVENTREGISTRY_HPP

#include "keto/event/Event.hpp"


namespace keto {
namespace block {

class EventRegistry {
public:
    EventRegistry(const EventRegistry& orig) = delete;
    virtual ~EventRegistry();
    
    static void registerEventHandlers();
    static void deregisterEventHandlers();
    
    static keto::event::Event blockMessage(const keto::event::Event& event);
private:
    EventRegistry();
    
};

}
}

#endif /* EVENTREGISTRY_HPP */

