/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TransactionTraceBuilder.hpp
 * Author: ubuntu
 *
 * Created on March 17, 2018, 5:04 AM
 */

#ifndef TRANSACTIONTRACEBUILDER_HPP
#define TRANSACTIONTRACEBUILDER_HPP

#include <string>
#include <memory>

#include "TransactionTrace.h"

#include "keto/asn1/HashHelper.hpp"
#include "keto/crypto/KeyLoader.hpp"

namespace keto {
namespace transaction_common {

class TransactionTraceBuilder;
typedef std::shared_ptr<TransactionTraceBuilder> TransactionTraceBuilderPtr;

class TransactionTraceBuilder {
public:
    TransactionTraceBuilder(const TransactionTraceBuilder& orig) = delete;
    virtual ~TransactionTraceBuilder();
    
    static TransactionTraceBuilderPtr createTransactionTrace(
        const keto::asn1::HashHelper& accountHash, keto::crypto::KeyLoader& keyloader);
    
    operator TransactionTrace_t*();
    operator TransactionTrace_t&();
    
    
private:
    TransactionTrace_t* transactionTrace;
    
    TransactionTraceBuilder(
        const keto::asn1::HashHelper& accountHash, keto::crypto::KeyLoader& keyloader);
    
    
};


}
}

#endif /* TRANSACTIONTRACEBUILDER_HPP */

