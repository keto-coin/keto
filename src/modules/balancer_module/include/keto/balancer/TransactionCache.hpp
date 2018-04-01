/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TransactionCache.hpp
 * Author: ubuntu
 *
 * Created on March 31, 2018, 4:23 PM
 */

#ifndef TRANSACTIONCACHE_HPP
#define TRANSACTIONCACHE_HPP

#include <string>
#include <memory>
#include <vector>
#include <set>

namespace keto {
namespace balancer {

typedef std::vector<uint8_t> TransactionIdHashVector;
class TransactionCache;
typedef std::shared_ptr<TransactionCache> TransactionCachePtr;

class TransactionCache {
public:
    TransactionCache();
    TransactionCache(const TransactionCache& orig) = delete;
    virtual ~TransactionCache();
    
    //void set
    static TransactionCachePtr init();
    static TransactionCachePtr getInstance();
    static void fin();
    
    bool isProcessed(TransactionIdHashVector transactionId);
    void processed(TransactionIdHashVector transactionId);
    
private:
    std::mutex classMutex;
    std::set<TransactionIdHashVector> processedTransactions;

};

    
}    
}
#endif /* TRANSACTIONCACHE_HPP */

