/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SandboxService.hpp
 * Author: ubuntu
 *
 * Created on April 10, 2018, 8:33 AM
 */

#ifndef SANDBOXSERVICE_HPP
#define SANDBOXSERVICE_HPP

#include <string>
#include <memory>

#include "keto/event/Event.hpp"

namespace keto {
namespace sandbox {

class SandboxService;
typedef std::shared_ptr<SandboxService> SandboxServicePtr;
    
class SandboxService {
public:
    SandboxService();
    SandboxService(const SandboxService& orig) = delete;
    virtual ~SandboxService();
    
    static SandboxServicePtr init();
    static void fin();
    static SandboxServicePtr getInstance();
    
    keto::event::Event executeActionMessage(const keto::event::Event& event);
private:
    std::string code;
};


}
}


#endif /* SANDBOXSERVICE_HPP */

