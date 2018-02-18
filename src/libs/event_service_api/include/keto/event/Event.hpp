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
    Event(std::vector<uint8_t> message) : 
        message(message)  {
    }
        
    Event(const std::string& name,std::vector<uint8_t> message) : 
        name(name),message(message)  {
    }
        
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
    
    Event& setName(const std::string& name) {
        this->name = name;
        return (*this);
    }
    
    std::string getSource() const {
        return this->source;
    }
    
    Event& setSource(const std::string& source)  {
        this->source = source;
        return (*this);
    }
    
    std::vector<uint8_t> getSourceHash() const {
        return this->sourceHash;
    }
    
    Event& setSourceHash(std::vector<uint8_t>& sourceHash) {
        this->sourceHash = sourceHash;
        return (*this);
    }
    
    std::vector<uint8_t> getSourceSignature() {
        return this->sourceSignature;
    }
    
    Event& setSourceSignature(const std::vector<uint8_t>& sourceSignature) {
        this->sourceSignature = sourceSignature;
        return (*this);
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

