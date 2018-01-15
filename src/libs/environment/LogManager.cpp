/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Log.cpp
 * Author: ubuntu
 * 
 * Created on January 13, 2018, 6:15 PM
 */

#include "keto/environment/LogManager.hpp"

namespace keto {
    namespace environment {
    
LogManager::LogManager(const std::shared_ptr<Config>& configPtr) : 
    configPtr(configPtr) {
    
    
}

LogManager::~LogManager() {
}

    
    }
}
