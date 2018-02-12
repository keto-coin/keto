/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BalancerModule.hpp
 * Author: ubuntu
 *
 * Created on February 10, 2018, 1:36 PM
 */

#ifndef BALANCERMODULE_HPP
#define BALANCERMODULE_HPP

#include <string>
#include <map>
#include <memory>

#include "keto/module/ModuleInterface.hpp"
#include "keto/common/MetaInfo.hpp"


namespace keto {
namespace balancer {


class BalancerModule : public keto::module::ModuleInterface {
public:
    BalancerModule();
    BalancerModule(const BalancerModule& orig) = delete;
    virtual ~BalancerModule();
    
    // meta methods
    virtual const std::string getName() const;
    virtual const std::string getDescription() const;
    virtual const std::string getVersion() const;

private:

};


}
}

#endif /* BALANCERMODULE_HPP */

