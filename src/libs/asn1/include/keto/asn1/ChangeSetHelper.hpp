/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ChangeSetHelper.hpp
 * Author: ubuntu
 *
 * Created on March 13, 2018, 10:54 AM
 */

#ifndef CHANGESETHELPER_HPP
#define CHANGESETHELPER_HPP

#include "Status.h"
#include "ChangeData.h"
#include "ChangeSet.h"



#include "keto/asn1/HashHelper.hpp"
#include "keto/asn1/SignatureHelper.hpp"

namespace keto {
namespace asn1 {


class ChangeSetHelper {
public:
    ChangeSetHelper();
    ChangeSetHelper(const HashHelper& transactionHash,const HashHelper& accountHash);
    ChangeSetHelper(const ChangeSetHelper& orig) = default;
    virtual ~ChangeSetHelper();
    
    ChangeSetHelper& setTransactionHash(const HashHelper& transactionHash);
    ChangeSetHelper& setAccountHash(const HashHelper& accountHash);
    ChangeSetHelper& setStatus(const Status_t status);
    ChangeSetHelper& addChange(const ANY_t& change);
    
    operator ChangeSet_t*();
    operator ANY_t*();
    
private:
    HashHelper transactionHash;
    HashHelper accountHash;
    Status_t status;
    std::vector<ANY_t> changes;
};


}
}


#endif /* CHANGESETHELPER_HPP */

