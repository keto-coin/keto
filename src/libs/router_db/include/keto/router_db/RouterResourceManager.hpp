/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RouterResourceManager.hpp
 * Author: ubuntu
 *
 * Created on February 28, 2018, 11:01 AM
 */

#ifndef ROUTER_RESOURCEMANAGER_HPP
#define ROUTER_RESOURCEMANAGER_HPP

#include <string>
#include <memory>

#include "keto/transaction/Resource.hpp"

#include "keto/rocks_db/DBManager.hpp"
#include "keto/router_db/RouterResource.hpp"


namespace keto {
namespace router_db {

class RouterResourceManager;
typedef std::shared_ptr<RouterResourceManager> RouterResourceManagerPtr;

    
class RouterResourceManager : keto::transaction::Resource {
public:
    RouterResourceManager(std::shared_ptr<keto::rocks_db::DBManager> dbManagerPtr);
    RouterResourceManager(const RouterResourceManager& orig) = delete;
    virtual ~RouterResourceManager();
    
    virtual void commit();
    virtual void rollback();
    
    RouterResourcePtr getResource();
    
private:
    static thread_local RouterResourcePtr blockResourcePtr;
    std::shared_ptr<keto::rocks_db::DBManager> dbManagerPtr;
};


}
}

#endif /* BLOCKRESOURCEMANAGER_HPP */

