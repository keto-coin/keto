/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Event.hpp
 * Author: ubuntu
 *
 * Created on January 19, 2018, 8:24 AM
 */

#ifndef EVENT_SERVICE_EVENT_OBJECT_HPP
#define EVENT_SERVICE_EVENT_OBJECT_HPP

#include <string>
#include <string.h>
#include <array>
#include <stdlib.h>

namespace keto {
namespace event {

class Event {
public:
    Event(const std::string& name,
            const std::string& source,
            const unsigned char* message,
            const unsigned char* signature) : 
        name(name),source(source) {
        
        this->message = (unsigned char *)malloc(sizeof(message)*sizeof(unsigned char));
        memcpy(&this->message,&message,sizeof(message));
        this->signature = (unsigned char *)malloc(sizeof(signature)*sizeof(unsigned char));
        memcpy(&this->signature,&signature,sizeof(message));
    }
    
    Event(const Event& orig) : name(orig.name),source(orig.source) {
        this->message = (unsigned char *)malloc(sizeof(message)*sizeof(unsigned char));
        memcpy(&this->message, &orig.message,sizeof(orig.message));
        this->signature = (unsigned char *)malloc(sizeof(signature)*sizeof(unsigned char));
        memcpy(&this->signature,&orig.signature,sizeof(orig.signature));
    }
    
    virtual ~Event() {
        free(this->message);
        free(this->signature);
    }
    
    std::string getName() const {
        return this->name;
    }
    
    std::string getSource() const {
        return this->source;
    }
    
    unsigned char* getMessage() {
        return this->message;
    }
    
    unsigned char* getSignature() {
        return this->signature;
    }
    
private:
    std::string name;
    std::string source;
    unsigned char* message;
    unsigned char* signature;
    
};

}
}


#endif /* EVENT_HPP */

