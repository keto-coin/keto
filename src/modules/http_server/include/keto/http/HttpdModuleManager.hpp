/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HttpModuleManager.hpp
 * Author: ubuntu
 *
 * Created on January 20, 2018, 12:32 PM
 */

#ifndef HTTPD_MODULEMANAGER_HPP
#define HTTPD_MODULEMANAGER_HPP

#include <string>
#include <map>
#include <memory>

#include "keto/module/ModuleManagementInterface.hpp"
#include "keto/http/HttpdModule.hpp"

namespace keto {
namespace http {


class HttpdModuleManager : public keto::module::ModuleManagementInterface {
public:
    HttpdModuleManager();
    HttpdModuleManager(const HttpdModuleManager& orig) = delete;
    virtual ~HttpdModuleManager();
    
    // meta methods
    virtual const std::string getName() const;
    virtual const std::string getDescription() const;
    virtual const std::string getVersion() const;
    
    // lifecycle methods
    virtual void start();
    virtual void stop();
    
    virtual const std::vector<std::string> listModules();
    virtual const std::shared_ptr<keto::module::ModuleInterface> getModule(const std::string& name);
    
    static boost::shared_ptr<HttpdModuleManager> create_module();
    
private:
    std::map<std::string,std::shared_ptr<keto::module::ModuleInterface>> modules;
};

}
}

#endif /* HTTPMODULEMANAGER_HPP */

