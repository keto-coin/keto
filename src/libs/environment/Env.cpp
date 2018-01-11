/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <cstdlib>
#include "keto/environment/Env.hpp"

namespace keto {
namespace environment {


Env::Env() {
    this->installDir = std::getenv("KETO_HOME");
    if (this->installDir.empty()) {
        
    }
    
}


Env::~Env(){
    
}


std::string Env::getInstallDir() {
    return this->installDir;
}

}
}