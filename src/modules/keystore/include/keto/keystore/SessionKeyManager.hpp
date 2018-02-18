/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SessionKeyManager.hpp
 * Author: ubuntu
 *
 * Created on February 17, 2018, 8:46 AM
 */

#ifndef SESSIONKEYMANAGER_HPP
#define SESSIONKEYMANAGER_HPP

#include <string>
#include <map>
#include <vector>
#include <mutex>

#include <botan/rng.h>
#include <botan/p11_randomgenerator.h>
#include <botan/auto_rng.h>


#include "keto/event/Event.hpp"
#include "keto/crypto/Containers.hpp"

namespace keto {
namespace keystore {


class SessionKeyManager {
public:
    SessionKeyManager();
    SessionKeyManager(const SessionKeyManager& orig) = delete;
    virtual ~SessionKeyManager();
    
    keto::event::Event requestKey(const keto::event::Event& event);
    void removeKey(const keto::event::Event& event);
    
private:
    std::unique_ptr<Botan::RandomNumberGenerator> rng;
    std::mutex mutex;
    std::map<std::vector<uint8_t>,keto::crypto::SecureVector> sessionKeys;

};

}
}

#endif /* SESSIONKEYMANAGER_HPP */

