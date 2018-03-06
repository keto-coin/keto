/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RouterStore.hpp
 * Author: ubuntu
 *
 * Created on March 6, 2018, 3:20 AM
 */

#ifndef ROUTERSTORE_HPP
#define ROUTERSTORE_HPP

#include <string>
#include <memory>

#include "Route.pb.h"

#include "keto/rocks_db/DBManager.hpp"

#include "keto/asn1/HashHelper.hpp"
#include "keto/router_db/RouterResourceManager.hpp"

namespace keto {
namespace router_db {

class RouterStore {
public:
    RouterStore();
    RouterStore(const RouterStore& orig) = delete;
    virtual ~RouterStore();
    
    // manage the store
    static std::shared_ptr<RouterStore> init();
    static void fin();
    static std::shared_ptr<RouterStore> getInstance();

    // get the account information
    bool getAccountRouting(
            const keto::asn1::HashHelper& helper,
            keto::proto::AccountRoutingStore& result);
    
    
    void setAccountRouting(
            const keto::asn1::HashHelper& helper,
            const keto::proto::AccountRoutingStore& routing);
    
private:
    std::shared_ptr<keto::rocks_db::DBManager> dbManagerPtr;
    RouterResourceManagerPtr routerResourceManagerPtr;

};


}
}

#endif /* ROUTERSTORE_HPP */

