/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EnvironmentManager.h
 * Author: Brett Chaldecott
 *
 * Created on January 10, 2018, 12:15 PM
 */

#ifndef ENVIRONMENTMANAGER_H
#define ENVIRONMENTMANAGER_H

#include <memory>

#include "keto/environment/Env.hpp"

namespace keto {
namespace environment {   

/**
 * The environment manager
 */
class EnvironmentManager {
public:
    EnvironmentManager();
    virtual ~EnvironmentManager();
    EnvironmentManager(const EnvironmentManager& orig) = delete;
    
    static std::shared_ptr<EnvironmentManager> init();
    static std::shared_ptr<EnvironmentManager> getInstance();
    
    
    std::shared_ptr<Env> getEnv();
    
private:
    
    std::shared_ptr<Env> envSharedPtr;
    
};

}
}

#endif /* ENVIRONMENTMANAGER_H */

