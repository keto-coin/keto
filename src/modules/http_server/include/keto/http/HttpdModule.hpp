/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HttpdModule.hpp
 * Author: ubuntu
 *
 * Created on January 20, 2018, 12:44 PM
 */

#ifndef HTTPDMODULE_HPP
#define HTTPDMODULE_HPP

#include <string>
#include <map>
#include <memory>

#include "keto/module/ModuleInterface.hpp"


namespace keto {
namespace http {


class HttpdModule : public keto::module::ModuleInterface {
public:
    HttpdModule();
    HttpdModule(const HttpdModule& orig) = delete;
    virtual ~HttpdModule();
    
    // meta methods
    virtual const std::string getName() const;
    virtual const std::string getDescription() const;
    virtual const std::string getVersion() const;
    
private:

};

}
}

#endif /* HTTPDMODULE_HPP */

