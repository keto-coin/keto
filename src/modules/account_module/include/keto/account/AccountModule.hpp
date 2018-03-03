/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AccountModule.hpp
 * Author: ubuntu
 *
 * Created on March 3, 2018, 11:53 AM
 */

#ifndef ACCOUNTMODULE_HPP
#define ACCOUNTMODULE_HPP

#include <string>
#include <map>
#include <memory>


#include "keto/module/ModuleInterface.hpp"
#include "keto/common/MetaInfo.hpp"


namespace keto {
namespace account {

class AccountModule : public keto::module::ModuleInterface {
public:
    AccountModule();
    AccountModule(const AccountModule& orig) = delete;
    virtual ~AccountModule();
    
    // meta methods
    virtual const std::string getName() const;
    virtual const std::string getDescription() const;
    virtual const std::string getVersion() const;

private:
    
};


}
}

#endif /* ACCOUNTMODULE_HPP */

