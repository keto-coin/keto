/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   WavmSessionScope.h
 * Author: brett chaldecott
 *
 * Created on May 10, 2018, 4:44 PM
 */

#ifndef WAVMSESSIONSCOPE_H
#define WAVMSESSIONSCOPE_H

#include "Sandbox.pb.h"

#include "keto/wavm_common/WavmSession.hpp"

namespace keto {
namespace wavm_common {

class WavmSessionScope {
public:
    WavmSessionScope(keto::proto::SandboxCommandMessage& sandboxCommandMessage);
    WavmSessionScope(const WavmSessionScope& orig) = default;
    virtual ~WavmSessionScope();
    
    WavmSessionPtr getSession();
private:
    
};

}
}

#endif /* WAVMSESSIONSCOPE_H */

