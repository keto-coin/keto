/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RpcClientModule.hpp
 * Author: ubuntu
 *
 * Created on January 20, 2018, 1:45 PM
 */

#ifndef RPCCLIENTMODULE_HPP
#define RPCCLIENTMODULE_HPP

#include <string>
#include <map>
#include <memory>

#include "keto/module/ModuleInterface.hpp"

namespace keto {
namespace rpc_client {

class RpcClientModule : public keto::module::ModuleInterface {
public:
    RpcClientModule();
    RpcClientModule(const RpcClientModule& orig) = delete;
    virtual ~RpcClientModule();
    
    // meta methods
    virtual const std::string getName() const;
    virtual const std::string getDescription() const;
    virtual const std::string getVersion() const;

    
private:

};

        
}
}

#endif /* RPCCLIENTMODULE_HPP */

