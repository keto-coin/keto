/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RouterRegistry.hpp
 * Author: ubuntu
 *
 * Created on March 30, 2018, 10:07 AM
 */

#ifndef ROUTERREGISTRY_HPP
#define ROUTERREGISTRY_HPP

#include <string>
#include <vector>
#include <memory>
#include <map>
#include <set>
#include <mutex>

namespace keto {
namespace router {

class RouterRegistry;
typedef std::shared_ptr<RouterRegistry> RouterRegistryPtr;
typedef std::vector<uint8_t> AccountHashVector;
    
class RouterRegistry {
public:
    RouterRegistry();
    RouterRegistry(const RouterRegistry& orig) = delete;
    virtual ~RouterRegistry();
    
    // singleton methods
    static RouterRegistryPtr init();
    static RouterRegistryPtr getInstance();
    static void fin();
    
    void registerService(const AccountHashVector& accountHash, const std::string& service);
    void registerServices(const AccountHashVector& accountHash, const std::vector<std::string>& services);
    
    std::vector<std::string> getServices(const std::vector<uint8_t>& accountHash);
    AccountHashVector getAccount(const std::string& service);
    bool isServiceLocal(const std::string& service);
    bool isAccountLocal(const AccountHashVector& accountHash);
    
private:
    std::mutex classMutex;
    std::map<std::string,std::set<AccountHashVector>> serviceAccountMap;
    std::map<AccountHashVector,std::set<std::string>> accountServiceMap;
    
};


}
}


#endif /* ROUTERREGISTRY_HPP */

