/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Events.hpp
 * Author: ubuntu
 *
 * Created on February 17, 2018, 12:45 PM
 */

#ifndef EVENTS_HPP
#define EVENTS_HPP

namespace keto {
namespace server_common {

class Events {
public:
    Events() = delete;
    Events(const Events& orig) = delete;
    virtual ~Events() = delete;
    
    // events for the key store
    static const char* REQUEST_SESSION_KEY;
    static const char* REMOVE_SESSION_KEY;
    
    // events for the router
    static const char* ROUTE_MESSAGE;
    static const char* REGISTER_SERVICE_MESSAGE;
    
    // account events
    static const char* CHECK_ACCOUNT_MESSAGE;
    static const char* APPLY_ACCOUNT_TRANSACTION_MESSAGE;
    
    // balancer
    static const char* BALANCER_MESSAGE;
    
    // balancer
    static const char* BLOCK_MESSAGE;
    
    // rpc messages
    static const char* RPC_SEND_MESSAGE;
    
    // sparql events
    static const char* SPARQL_QUERY_MESSAGE;
    
private:

};


}
}


#endif /* EVENTS_HPP */

