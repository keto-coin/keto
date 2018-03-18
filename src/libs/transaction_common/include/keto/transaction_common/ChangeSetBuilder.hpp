/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ChangeSetBuilder.hpp
 * Author: ubuntu
 *
 * Created on March 17, 2018, 3:51 AM
 */

#ifndef CHANGESETBUILDER_HPP
#define CHANGESETBUILDER_HPP

#include <string>
#include <memory>

#include "Status.h"
#include "ChangeSet.h"

#include "keto/asn1/HashHelper.hpp"


namespace keto {
namespace transaction_common {

class ChangeSetBuilder;
typedef std::shared_ptr<ChangeSetBuilder> ChangeSetBuilderPtr;

class ChangeSetBuilder {
public:
    ChangeSetBuilder();
    ChangeSetBuilder(const keto::asn1::HashHelper& transactionHash, 
        const keto::asn1::HashHelper& accountHash);
    ChangeSetBuilder(const ChangeSetBuilder& orig) = delete;
    virtual ~ChangeSetBuilder();
    
    ChangeSetBuilder& setTransaction(const keto::asn1::HashHelper& transactionHash);
    ChangeSetBuilder& setAccount(const keto::asn1::HashHelper& accountHash);
    ChangeSetBuilder& setStatus(const Status& status);
    ChangeSetBuilder& addChange(const ANY_t& asn1Change);
    
    operator ChangeSet_t*();
    operator ChangeSet_t&();
    
private:
    ChangeSet_t* changeSet;
    
};


}
}


#endif /* CHANGESETBUILDER_HPP */

