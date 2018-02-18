/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EventServiceHelpers.hpp
 * Author: ubuntu
 *
 * Created on February 18, 2018, 4:40 AM
 */

#ifndef KETO_EVENT_SERVICEHELPERS_HPP
#define KETO_EVENT_SERVICEHELPERS_HPP

#include <memory>

#include "keto/event/Event.hpp"
#include "keto/event/EventServiceInterface.hpp"

#include "keto/server_common/EventUtils.hpp"
#include "keto/server_common/ServerInfo.hpp"
#include "keto/server_common/VectorUtils.hpp"

namespace keto {
namespace server_common {

void triggerEvent(const keto::event::Event& event);

keto::event::Event processEvent(const keto::event::Event& event);

void registerEventHandler(const std::string& name, keto::event::handler handlerMethod);

void deregisterEventHandler(const std::string& name);

    
}
}


#endif /* EVENTSERVICEHELPERS_HPP */

