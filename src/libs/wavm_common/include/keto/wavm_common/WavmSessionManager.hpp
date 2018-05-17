/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   WavmSessionManager.hpp
 * Author: ubuntu
 *
 * Created on May 10, 2018, 11:01 AM
 */

#ifndef WAVMSESSIONMANAGER_HPP
#define WAVMSESSIONMANAGER_HPP

#include <string>
#include <memory>

#include "Sandbox.pb.h"

#include "keto/wavm_common/WavmSession.hpp"
#include "keto/crypto/KeyLoader.hpp"

namespace keto {
namespace wavm_common {

class WavmSessionManager;
typedef std::shared_ptr<WavmSessionManager> WavmSessionManagerPtr;
    
class WavmSessionManager {
public:
    WavmSessionManager();
    WavmSessionManager(const WavmSessionManager& orig) = delete;
    virtual ~WavmSessionManager();
    
    static WavmSessionManagerPtr init();
    static void fin();
    static WavmSessionManagerPtr getInstance();
    
    WavmSessionPtr initWavmSession(const keto::proto::SandboxCommandMessage& sandboxCommandMessage);
    WavmSessionPtr getWavmSession();
    void finWavmSession();
    
private:
    // thread local reference to a wavm session. This is effectively a map indexed on thread id.
    static thread_local WavmSessionPtr wavmSessionPtr;
    
    // private member variables
    keto::crypto::KeyLoaderPtr keyLoaderPtr;
};


}
}


#endif /* WAVMSESSIONMANAGER_HPP */

