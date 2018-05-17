/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SandboxService.cpp
 * Author: ubuntu
 * 
 * Created on April 10, 2018, 8:33 AM
 */

#include <boost/filesystem/path.hpp>
#include <iostream>
#include <sstream>

#include <condition_variable>

#include <botan/hex.h>

#include "Sandbox.pb.h"

#include "keto/server_common/EventUtils.hpp"
#include "keto/server_common/Events.hpp"
#include "keto/server_common/EventServiceHelpers.hpp"

#include "keto/common/Log.hpp"
#include "keto/common/Exception.hpp"

#include "keto/sandbox/SandboxService.hpp"
#include "keto/wavm_common/WavmEngineManager.hpp"
#include "keto/wavm_common/WavmSessionManager.hpp"
#include "keto/wavm_common/WavmSessionScope.hpp"
#include "keto/environment/EnvironmentManager.hpp"
#include "keto/server_common/VectorUtils.hpp"


namespace keto {
namespace sandbox {

static SandboxServicePtr singleton;

SandboxService::SandboxService() {
    boost::filesystem::path helloFile =  
            keto::environment::EnvironmentManager::getInstance()->getEnv()->getInstallDir() / 
            "config/helloworld.wast";
    std::ifstream ifs(helloFile.string());
    char character;
    std::stringstream ss;
    while (ifs.get(character)) {
        ss << character;
    }
    this->code = ss.str();
}

SandboxService::~SandboxService() {
}


SandboxServicePtr SandboxService::init() {
    return singleton = std::make_shared<SandboxService>();
}

void SandboxService::fin() {
    singleton.reset();
}

SandboxServicePtr SandboxService::getInstance() {
    return singleton;
}

keto::event::Event SandboxService::executeActionMessage(const keto::event::Event& event) {
    std::cout << "Extract the event information" << std::endl;
    keto::proto::SandboxCommandMessage sandboxCommandMessage =
            keto::server_common::fromEvent<keto::proto::SandboxCommandMessage>(event);
    std::cout << "After extracting the event information : " << sandboxCommandMessage.contract() << std::endl;
    
    try {
        keto::wavm_common::WavmSessionScope wavmSessionScope(sandboxCommandMessage);
        std::string buffer = sandboxCommandMessage.contract();
        std::cout << "The buffer : " << buffer << std::endl;
        std::string code = keto::server_common::VectorUtils().copyVectorToString(Botan::hex_decode(
                buffer,true));
        std::cout << "The code : " << code << std::endl;
        keto::wavm_common::WavmEngineManager::getInstance()->getEngine(code)->execute();
        
        sandboxCommandMessage = wavmSessionScope.getSession()->getSandboxCommandMessage();
        
    } catch (keto::common::Exception& ex) {
        KETO_LOG_ERROR << "Failed to process the contract : " << ex.what();
        KETO_LOG_ERROR << "Cause: " << boost::diagnostic_information(ex,true);
        throw ex;
    } catch (boost::exception& ex) {
        KETO_LOG_ERROR << "Failed to process the contract : " << boost::diagnostic_information(ex,true);
        throw;
    } catch (std::exception& ex) {
        KETO_LOG_ERROR << "Failed to process the contract : " << ex.what();
        throw ex;
    } catch (...) {
        KETO_LOG_INFO << "Failed to process the contract";
        throw;
    }
    return keto::server_common::toEvent<keto::proto::SandboxCommandMessage>(sandboxCommandMessage);
}

}
}