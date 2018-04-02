/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BlockProducer.hpp
 * Author: ubuntu
 *
 * Created on April 2, 2018, 10:38 AM
 */

#ifndef BLOCKPRODUCER_HPP
#define BLOCKPRODUCER_HPP

#include <string>
#include <thread>
#include <memory>
#include <deque>
#include <mutex>
#include <condition_variable>


#include "BlockChain.pb.h"

namespace keto {
namespace block {
    
class BlockProducer;
typedef std::shared_ptr<BlockProducer> BlockProducerPtr;

class BlockProducer {
public:
    /**
     * The state enum containing the various states that the module manager can
     * be in.
     */
    enum State {
        inited,
        producing,
        terminated
    };
    
    BlockProducer();
    BlockProducer(const BlockProducer& orig) = delete;
    virtual ~BlockProducer();
    
    static BlockProducerPtr init();
    static void fin();
    static BlockProducerPtr getInstance();
    
    void run();
    void terminate();
    
    void addTransaction(keto::proto::Transaction transaction);
    
private:
    State currentState;
    std::condition_variable stateCondition;
    std::mutex classMutex;
    std::deque<keto::proto::Transaction> transactions;
    
    
    State checkState();
    std::deque<keto::proto::Transaction> getTransactions();
    void generateBlock(const std::deque<keto::proto::Transaction>& transactions);
};


}
}


#endif /* BLOCKPRODUCER_HPP */

