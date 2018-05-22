/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RouterService.hpp
 * Author: ubuntu
 *
 * Created on March 2, 2018, 4:04 PM
 */

#ifndef ROUTERSERVICE_HPP
#define ROUTERSERVICE_HPP

#include <string>
#include <memory>


#include "Protocol.pb.h"

#include "keto/event/Event.hpp"


namespace keto {
namespace router {
        

class RouterService {
public:
    RouterService(const RouterService& orig) = delete;
    virtual ~RouterService();
    
    static std::shared_ptr<RouterService> init();
    static void fin();
    static std::shared_ptr<RouterService> getInstance();
    
    
    keto::event::Event routeMessage(const keto::event::Event& event);
    keto::event::Event registerService(const keto::event::Event& event);
    keto::event::Event updateStateRouteMessage(const keto::event::Event& event);
    
    
private:
    RouterService();
    
    /**
     * This method is called to route a message locally.
     * 
     * @param messageWrapper The message wrapper
     */
    void routeLocal(keto::proto::MessageWrapper&  messageWrapper);
    
    /**
     * This method is called to route a message locally.
     * 
     * @param messageWrapper The message wrapper
     */
    void routeToAccount(keto::proto::MessageWrapper&  messageWrapper);
    
};


}
}

#endif /* ROUTERSERVICE_HPP */

