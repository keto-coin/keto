/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ServiceRegistryHelper.cpp
 * Author: ubuntu
 * 
 * Created on March 31, 2018, 4:45 AM
 */


#include <vector>

#include "Route.pb.h"

#include "keto/server_common/ServiceRegistryHelper.hpp"
#include "keto/server_common/ServerInfo.hpp"
#include "keto/server_common/VectorUtils.hpp"
#include "keto/server_common/EventServiceHelpers.hpp"
#include "include/keto/server_common/Events.hpp"

namespace keto {
namespace server_common {
    
void registerService(const std::string& service) {
    std::vector<uint8_t> accountVector = ServerInfo::getInstance()->getAccountHash();
    
    keto::proto::PushService pushService;
    pushService.set_account(VectorUtils().copyVectorToString(accountVector));
    pushService.set_service_name(service);
    
    keto::server_common::triggerEvent(keto::server_common::toEvent<keto::proto::PushService>(
            keto::server_common::Events::REGISTER_SERVICE_MESSAGE,pushService));
}

}
}
