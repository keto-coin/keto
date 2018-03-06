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

#include "SignedBlock.h"

#include "keto/rocks_db/DBManager.hpp"
#include "keto/router_db/RouterResourceManager.hpp"

namespace keto {
namespace router_db {

class RouterStore {
public:
    RouterStore();
    RouterStore(const RouterStore& orig) = delete;
    virtual ~RouterStore();
    
    static std::shared_ptr<RouterStore> init();
    static void fin();
    static std::shared_ptr<RouterStore> getInstance();

private:
    std::shared_ptr<keto::rocks_db::DBManager> dbManagerPtr;
    RouterResourceManagerPtr routerResourceManagerPtr;

};


}
}

#endif /* ROUTERSTORE_HPP */

