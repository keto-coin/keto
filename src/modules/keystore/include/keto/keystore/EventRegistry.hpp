/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EventRegistry.hpp
 * Author: ubuntu
 *
 * Created on February 17, 2018, 12:29 PM
 */

#ifndef EVENTREGISTRY_HPP
#define EVENTREGISTRY_HPP

#include "keto/event/Event.hpp"


namespace keto {
namespace keystore {


class EventRegistry {
public:
    EventRegistry(const EventRegistry& orig) = delete;
    virtual ~EventRegistry();
    
    static keto::event::Event requestSessionKey(const keto::event::Event& event);
    static keto::event::Event removeSessionKey(const keto::event::Event& event);
    
    
    static void registerEventHandlers();
    static void deregisterEventHandlers();
private:
    EventRegistry();
    
};


}
}

#endif /* EVENTREGISTRY_HPP */

