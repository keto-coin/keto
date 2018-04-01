/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BlockRouting.hpp
 * Author: ubuntu
 *
 * Created on March 31, 2018, 4:25 PM
 */

#ifndef BLOCKROUTING_HPP
#define BLOCKROUTING_HPP

#include <string>
#include <vector>
#include <memory>
#include <mutex>

namespace keto {
namespace balancer {

typedef std::vector<uint8_t> AccountHashVector;
class BlockRouting;
typedef std::shared_ptr<BlockRouting> BlockRoutingPtr;

class BlockRouting {
public:
    BlockRouting();
    BlockRouting(const BlockRouting& orig) = delete;
    virtual ~BlockRouting();
    
    //void set
    static BlockRoutingPtr init();
    static BlockRoutingPtr getInstance();
    static void fin();
    
    std::vector<AccountHashVector> getBlockAccounts();
    void setBlockAccounts(const std::vector<AccountHashVector>& accounts);
    
private:
    std::mutex classMutex;
    std::vector<AccountHashVector> accounts;

};


}
}

#endif /* BLOCKROUTING_HPP */

