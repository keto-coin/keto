/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RouterModule.hpp
 * Author: ubuntu
 *
 * Created on February 9, 2018, 11:11 AM
 */

#ifndef ROUTERMODULE_HPP
#define ROUTERMODULE_HPP

#include <string>
#include <map>
#include <memory>

#include "keto/module/ModuleInterface.hpp"
#include "keto/common/MetaInfo.hpp"

namespace keto {
namespace router {


class RouterModule : public keto::module::ModuleInterface {
public:
    RouterModule();
    RouterModule(const RouterModule& orig) = delete;
    virtual ~RouterModule();
    
    // meta methods
    virtual const std::string getName() const;
    virtual const std::string getDescription() const;
    virtual const std::string getVersion() const;

private:

};

}
}

#endif /* ROUTERMODULE_HPP */

