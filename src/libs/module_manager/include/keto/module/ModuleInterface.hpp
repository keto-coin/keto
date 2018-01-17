/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ModuleInterface.hpp
 * Author: ubuntu
 *
 * Created on January 17, 2018, 7:40 AM
 */

#ifndef MODULEINTERFACE_HPP
#define MODULEINTERFACE_HPP

namespace keto {
namespace module {

class ModuleInterface {
public:
    // meta methods
    virtual std::string getName() const = 0;
    virtual std::string getDescription() const = 0;
    virtual std::string getVersion() const = 0;
    
    
    
};

}
}
#endif /* MODULEINTERFACE_HPP */

