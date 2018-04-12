/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   WavmEngineManager.hpp
 * Author: ubuntu
 *
 * Created on April 9, 2018, 9:12 AM
 */

#ifndef WAVMENGINEMANAGER_HPP
#define WAVMENGINEMANAGER_HPP

#include <string>
#include <memory>

#include "keto/wavm_common/WavmEngineWrapper.hpp"

namespace keto {
namespace wavm_common {

class WavmEngineManager;
typedef std::shared_ptr<WavmEngineManager> WavmEngineManagerPtr;

class WavmEngineManager {
public:
    WavmEngineManager();
    WavmEngineManager(const WavmEngineManager& orig) = delete;
    virtual ~WavmEngineManager();
    
    
    static WavmEngineManagerPtr init();
    static void fin();
    static WavmEngineManagerPtr getInstance();
    
    WavmEngineWrapperPtr getEngine(const std::string& wast);
    
private:

};


}
}

#endif /* WAVMENGINEMANAGER_HPP */

