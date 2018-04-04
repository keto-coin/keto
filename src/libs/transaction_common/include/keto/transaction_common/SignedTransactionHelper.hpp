/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SignedTransactionHelper.hpp
 * Author: ubuntu
 *
 * Created on April 3, 2018, 9:39 AM
 */

#ifndef SIGNEDTRANSACTIONHELPER_HPP
#define SIGNEDTRANSACTIONHELPER_HPP

#include <string>
#include <memory>

#include "SignedTransaction.h"

#include "keto/asn1/HashHelper.hpp"
#include "keto/asn1/SignatureHelper.hpp"

#include "keto/transaction_common/TransactionHelper.hpp"

namespace keto {
namespace transaction_common {

class SignedTransactionHelper;
typedef std::shared_ptr<SignedTransactionHelper> SignedTransactionHelperPtr;

class SignedTransactionHelper {
public:
    SignedTransactionHelper(SignedTransaction_t* signedTransaction);
    SignedTransactionHelper(const SignedTransactionHelper& orig) = delete;
    virtual ~SignedTransactionHelper();
    
    keto::asn1::HashHelper getHash();
    keto::asn1::SignatureHelper getSignature();
    TransactionHelperPtr getTransaction();
private:
    SignedTransaction_t* signedTransaction;
    
    
};


}
}


#endif /* SIGNEDTRANSACTIONHELPER_HPP */

