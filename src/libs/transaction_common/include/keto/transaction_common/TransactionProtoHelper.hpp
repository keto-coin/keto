/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TransactionProtoHelper.hpp
 * Author: ubuntu
 *
 * Created on March 19, 2018, 7:59 AM
 */

#ifndef TRANSACTIONPROTOHELPER_HPP
#define TRANSACTIONPROTOHELPER_HPP

#include <string>
#include <memory>

#include "BlockChain.pb.h"
#include "TransactionMessage.h"

#include "keto/transaction_common/TransactionMessageHelper.hpp"

namespace keto {
namespace transaction_common {

class TransactionProtoHelper;
typedef std::shared_ptr<TransactionProtoHelper> TransactionProtoHelperPtr;

class TransactionProtoHelper {
public:
    TransactionProtoHelper();
    TransactionProtoHelper(const keto::proto::Transaction& transaction);
    TransactionProtoHelper(const TransactionMessageHelperPtr& transactionMessageHelper);
    TransactionProtoHelper(const TransactionProtoHelper& orig) = default;
    virtual ~TransactionProtoHelper();
    
    TransactionProtoHelper& setTransaction(const TransactionMessageHelperPtr& transactionMessageHelper);
    TransactionProtoHelper& setTransaction(const std::string& buffer);
    
    operator std::string();
    operator keto::proto::Transaction&();
    TransactionProtoHelper& operator = (const keto::proto::Transaction& transaction);
    
    TransactionMessageHelperPtr getTransactionMessageHelper();
    
private:
    keto::proto::Transaction transaction;
};


}
}

#endif /* TRANSACTIONPROTOHELPER_HPP */

