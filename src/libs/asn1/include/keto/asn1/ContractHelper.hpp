/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ContractHelper.hpp
 * Author: ubuntu
 *
 * Created on May 8, 2018, 6:35 AM
 */

#ifndef CONTRACTHELPER_HPP
#define CONTRACTHELPER_HPP

#include <string>

#include "Contract.h"
#include "keto/common/StringCodec.hpp"
#include "keto/crypto/Containers.hpp"

#include "keto/asn1/HashHelper.hpp"

namespace keto {
namespace asn1 {

class ContractHelper {
public:
    ContractHelper();
    ContractHelper(const Contract_t& contract);
    ContractHelper(const std::string& contract);
    ContractHelper(const ContractHelper& orig);
    virtual ~ContractHelper();
    
    ContractHelper& setId(const HashHelper& id);
    HashHelper getId();
    
    ContractHelper& setName(const std::string& name);
    std::string getName();
    
    ContractHelper& setOwner(const HashHelper& owner);
    HashHelper getOwner();
    
    ContractHelper& setPermissions(const std::vector<HashHelper>& permissions);
    std::vector<HashHelper> getPermissions();
    
    ContractHelper& setCode(const std::string& code);
    std::string getCode();
    
    operator Contract*();
    operator std::string();
    ContractHelper& operator=(const Contract_t& contract);
    
private:
    Contract_t* contract;
};


}
}

#endif /* CONTRACTHELPER_HPP */

