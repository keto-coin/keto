/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "keto/server_common/EventServiceHelpers.hpp"

namespace keto {
namespace server_common {

void triggerEvent(const keto::event::Event& event) {
    std::dynamic_pointer_cast<keto::event::EventServiceInterface>(keto::module::ModuleManager::getInstance()->getModule(keto::event::EventServiceInterface::KETO_EVENT_SERVICE_MODULE))->triggerEvent(event);
}

keto::event::Event processEvent(const keto::event::Event& event) {
    return std::dynamic_pointer_cast<keto::event::EventServiceInterface>(keto::module::ModuleManager::getInstance()->getModule(keto::event::EventServiceInterface::KETO_EVENT_SERVICE_MODULE))->processEvent(event);
}

void registerEventHandler(const std::string& name, keto::event::handler handlerMethod) {
    std::shared_ptr<keto::event::EventServiceInterface> ptr = std::dynamic_pointer_cast<keto::event::EventServiceInterface>(keto::module::ModuleManager::getInstance()->getModule(keto::event::EventServiceInterface::KETO_EVENT_SERVICE_MODULE));
    ptr->registerEventHandler(name,handlerMethod);
}

void deregisterEventHandler(const std::string& name) {
    std::shared_ptr<keto::event::EventServiceInterface> ptr = std::dynamic_pointer_cast<keto::event::EventServiceInterface>(keto::module::ModuleManager::getInstance()->getModule(keto::event::EventServiceInterface::KETO_EVENT_SERVICE_MODULE));
    ptr->deregisterEventHandler(name);
}

}
}