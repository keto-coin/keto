/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   KeystoreModule.hpp
 * Author: ubuntu
 *
 * Created on January 20, 2018, 4:41 PM
 */

#ifndef KEYSTOREMODULE_HPP
#define KEYSTOREMODULE_HPP

#include <string>
#include <map>
#include <memory>

#include "keto/module/ModuleInterface.hpp"

namespace keto {
namespace keystore {

class KeystoreModule : public keto::module::ModuleInterface {
public:
    KeystoreModule();
    KeystoreModule(const KeystoreModule& orig) = delete;
    virtual ~KeystoreModule();
    
    // meta methods
    virtual const std::string getName() const;
    virtual const std::string getDescription() const;
    virtual const std::string getVersion() const;

private:

};

}
}

#endif /* KEYSTOREMODULE_HPP */

