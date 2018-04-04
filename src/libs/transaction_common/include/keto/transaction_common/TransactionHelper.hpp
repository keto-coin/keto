/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TransactionHelper.hpp
 * Author: ubuntu
 *
 * Created on April 3, 2018, 10:40 AM
 */

#ifndef KETO_COMMON_TRANSACTIONHELPER_HPP
#define KETO_COMMON_TRANSACTIONHELPER_HPP

#include <string>
#include <memory>
#include <vector>

#include "Transaction.h"
#include "keto/asn1/NumberHelper.hpp"
#include "keto/asn1/TimeHelper.hpp"
#include "keto/asn1/HashHelper.hpp"
#include "keto/asn1/AnyInterface.hpp"

#include "keto/transaction_common/ActionHelper.hpp"

namespace keto {
namespace transaction_common {
    
class TransactionHelper;
typedef std::shared_ptr<TransactionHelper> TransactionHelperPtr;
        
class TransactionHelper {
public:
    TransactionHelper(Transaction* transaction);
    TransactionHelper(const TransactionHelper& orig) = delete;
    virtual ~TransactionHelper();
    
    long getVersion();
    keto::asn1::NumberHelper getValue();
    keto::asn1::HashHelper getParent();
    keto::asn1::TimeHelper getDate();
    keto::asn1::HashHelper getSourceAccount();
    keto::asn1::HashHelper getTargetAccount();
    
    std::vector<ActionHelperPtr> getActions();
    
    
private:
    Transaction* transaction;
};


}
}


#endif /* TRANSACTIONHELPER_HPP */

