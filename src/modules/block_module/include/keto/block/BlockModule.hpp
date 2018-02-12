/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BlockModule.hpp
 * Author: ubuntu
 *
 * Created on February 10, 2018, 3:21 PM
 */

#ifndef BLOCKMODULE_HPP
#define BLOCKMODULE_HPP

#include <string>
#include <map>
#include <memory>

#include "keto/module/ModuleInterface.hpp"
#include "keto/common/MetaInfo.hpp"


namespace keto {
namespace block {

class BlockModule : public keto::module::ModuleInterface {
public:
    BlockModule();
    BlockModule(const BlockModule& orig) = delete;
    virtual ~BlockModule();
    
    // meta methods
    virtual const std::string getName() const;
    virtual const std::string getDescription() const;
    virtual const std::string getVersion() const;
    
private:

};


}
}


#endif /* BLOCKMODULE_HPP */

