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

#ifndef BASIC_EVENT_SERVICE_EVENT_OBJECT_HPP
#define BASIC_EVENT_SERVICE_EVENT_OBJECT_HPP

#include <string>
#include <vector>
#include <array>
#include <stdlib.h>

namespace keto {
namespace event {

class Event {
public:
    Event(const std::string& name,
            const std::string& source,
            std::vector<uint8_t> sourceHash,
            std::vector<uint8_t> sourceSignature,
            std::vector<uint8_t> message) : 
        name(name),source(source), sourceHash(sourceHash), 
                sourceSignature(sourceSignature),message(message)  {
    }
    
    Event(const Event& orig) = default;
    
    virtual ~Event() {
    }
    
    std::string getName() const {
        return this->name;
    }
    
    std::string getSource() const {
        return this->source;
    }
    
    std::vector<uint8_t> getSourceHash() const {
        return this->sourceHash;
    }
    
    std::vector<uint8_t> getSourceSignature() {
        return this->sourceSignature;
    }
    std::vector<uint8_t> getMessage() {
        return this->message;
    }
    
private:
    std::string name;
    std::string source;
    std::vector<uint8_t> sourceHash;
    std::vector<uint8_t> sourceSignature;
    std::vector<uint8_t> message;
    
};

}
}


#endif /* EVENT_HPP */

