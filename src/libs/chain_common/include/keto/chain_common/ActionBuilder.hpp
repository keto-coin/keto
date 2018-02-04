/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ActionBuilder.hpp
 * Author: brett chaldecott
 *
 * Created on February 3, 2018, 10:16 AM
 */

#ifndef ACTIONBUILDER_HPP
#define ACTIONBUILDER_HPP

#include <memory>

#include "Hash.h"
#include "Number.h"
#include "ANY.h"

#include "Action.h"
#include "keto/common/MetaInfo.hpp"
#include "keto/asn1/TimeHelper.hpp"
#include "keto/asn1/HashHelper.hpp"
#include "keto/asn1/NumberHelper.hpp"
#include "keto/asn1/AnyInterface.hpp"
#include "keto/asn1/AnyHelper.hpp"


namespace keto {
namespace chain_common {


class ActionBuilder : virtual public keto::asn1::AnyInterface {
public:
    friend class TransactionBuilder;
    
    ActionBuilder(const ActionBuilder& orig) = delete;
    virtual ~ActionBuilder();
    
    static std::shared_ptr<ActionBuilder> createAction();
    
    long getVersion();
    
    keto::asn1::TimeHelper getDate();
    ActionBuilder& setDate(const keto::asn1::TimeHelper& date);
    
    keto::asn1::HashHelper getContract();
    ActionBuilder& setContract(const keto::asn1::HashHelper& contract);
    
    keto::asn1::HashHelper getSourceAccount();
    ActionBuilder& setSourceAccount(const keto::asn1::HashHelper& sourceAccount);
    
    keto::asn1::HashHelper getTargetAccount();
    ActionBuilder& setTargetAccount(const keto::asn1::HashHelper& targetAccount);
    
    keto::asn1::NumberHelper getValue();
    ActionBuilder& setValue(const keto::asn1::NumberHelper& value);
    
    keto::asn1::HashHelper getParent();
    ActionBuilder& setParent(const keto::asn1::HashHelper& parent);
    
    
    keto::asn1::AnyHelper getModel();
    ActionBuilder& setModel(keto::asn1::AnyHelper& anyHelper);
    
    virtual void* getPtr();
    virtual struct asn_TYPE_descriptor_s* getType();
    
protected:
    Action* takePtr();
    
private:
    Action* action;
    
    ActionBuilder();
    
    
};


}
}

#endif /* ACTIONBUILDER_HPP */

