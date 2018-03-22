/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TransactionMessageHelper.hpp
 * Author: ubuntu
 *
 * Created on March 17, 2018, 4:21 AM
 */

#ifndef TRANSACTIONMESSAGEHELPER_HPP
#define TRANSACTIONMESSAGEHELPER_HPP

#include <string>
#include <memory>
#include <vector>

#include "Transaction.h"
#include "SignedTransaction.h"
#include "SignedChangeSet.h"
#include "TransactionMessage.h"
#include "TransactionTrace.h"

#include "keto/asn1/HashHelper.hpp"
#include "keto/asn1/SignatureHelper.hpp"

namespace keto {
namespace transaction_common {

class TransactionMessageHelper;
typedef std::shared_ptr<TransactionMessageHelper> TransactionMessageHelperPtr;

class TransactionMessageHelper {
public:
    TransactionMessageHelper();
    TransactionMessageHelper(SignedTransaction_t* signedTransaction);
    TransactionMessageHelper(SignedTransaction_t* signedTransaction,
            const keto::asn1::HashHelper& sourceAccount, 
            const keto::asn1::HashHelper& targetAccount);
    TransactionMessageHelper(TransactionMessage_t* transactionMessage);
    TransactionMessageHelper(const std::string& transactionMessage);
    TransactionMessageHelper(const TransactionMessageHelper& orig) = delete;
    virtual ~TransactionMessageHelper();
    
    TransactionMessageHelper& setSignedTransaction(SignedTransaction_t* signedTransaction);
    TransactionMessageHelper& setSourceAccount(const keto::asn1::HashHelper& sourceAccount);
    TransactionMessageHelper& setTargetAccount(const keto::asn1::HashHelper& targetAccount);
    TransactionMessageHelper& setStatus(const Status& status);
    TransactionMessageHelper& addTransactionTrace(TransactionTrace_t* transactionTrace);
    TransactionMessageHelper& addChangeSet(SignedChangeSet_t* signedChangeSet);
    
    TransactionMessageHelper& operator =(const std::string& transactionMessage);
    operator TransactionMessage_t&();
    operator TransactionMessage_t*();
    operator ANY_t*();
    
    operator std::vector<uint8_t>();
    
    keto::asn1::HashHelper getSourceAccount();
    keto::asn1::HashHelper getTargetAccount();
    keto::asn1::HashHelper getHash();
    keto::asn1::SignatureHelper getSignature();
    
private:
    TransactionMessage_t* transactionMessage;
};


}
}

#endif /* TRANSACTIONMESSAGEHELPER_HPP */

