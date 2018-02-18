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
    
    static const char* REQUEST_SESSION_KEY;
    static const char* REMOVE_SESSION_KEY;

private:

};


}
}


#endif /* EVENTS_HPP */

