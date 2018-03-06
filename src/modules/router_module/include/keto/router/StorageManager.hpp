/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StorageManager.hpp
 * Author: ubuntu
 *
 * Created on March 6, 2018, 6:13 AM
 */

#ifndef STORAGEMANAGER_HPP
#define STORAGEMANAGER_HPP

#include <string>
#include <memory>

namespace keto {
namespace router {


class StorageManager {
public:
    StorageManager(const StorageManager& orig) = delete;
    virtual ~StorageManager();
    
    static std::shared_ptr<StorageManager> init();
    static void fin();
    static std::shared_ptr<StorageManager> getInstance();

private:
    StorageManager();

};


}
}

#endif /* STORAGEMANAGER_HPP */

