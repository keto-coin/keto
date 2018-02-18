/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   KeyStoreService.hpp
 * Author: ubuntu
 *
 * Created on February 17, 2018, 8:36 AM
 */

#ifndef KEYSTORESERVICE_HPP
#define KEYSTORESERVICE_HPP

#include <string>
#include <memory>

#include "keto/keystore/SessionKeyManager.hpp"

namespace keto {
namespace keystore {

class KeyStoreService {
public:
    KeyStoreService(const KeyStoreService& orig) = delete;
    virtual ~KeyStoreService();
    
    static std::shared_ptr<KeyStoreService> init();
    static void fin();
    static std::shared_ptr<KeyStoreService> getInstance();
    
    /**
     * This method returns the session key manager.
     * 
     * @return The reference to the session key manager.
     */
    std::shared_ptr<SessionKeyManager> getSessionKeyManager();
    
private:
    std::shared_ptr<SessionKeyManager> sessionKeyManager;
    
    KeyStoreService();
    
};


}
}


#endif /* KEYSTORESERVICE_HPP */

