/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ActionHelper.hpp
 * Author: ubuntu
 *
 * Created on April 4, 2018, 9:12 AM
 */

#ifndef ACTIONHELPER_HPP
#define ACTIONHELPER_HPP

#include <map>
#include <vector>
#include <string>

#include "Action.h"

#include "keto/asn1/TimeHelper.hpp"
#include "keto/asn1/HashHelper.hpp"
#include "keto/asn1/AnyHelper.hpp"

namespace keto {
namespace transaction_common {

class ActionHelper;
typedef std::shared_ptr<ActionHelper> ActionHelperPtr;
    
class ActionHelper {
public:
    ActionHelper(Action_t* action);
    ActionHelper(const ActionHelper& orig) = delete;
    virtual ~ActionHelper();
    
    keto::asn1::TimeHelper getDate();
    keto::asn1::HashHelper getContract();
    keto::asn1::HashHelper getParent();
    keto::asn1::AnyHelper  getModel();
    
    
private:
    Action_t* action;
};


}
}


#endif /* ACTIONHELPER_HPP */

