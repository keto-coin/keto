/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BlockModuleManager.cpp
 * Author: Brett Chaldecott
 * 
 * Created on February 10, 2018, 3:34 PM
 */

#include <boost/dll/alias.hpp>
#include <boost/dll/shared_library.hpp>
#include <boost/shared_ptr.hpp>

#include "keto/common/Log.hpp"
#include "keto/common/MetaInfo.hpp"
#include "keto/block/BlockModuleManager.hpp"
#include "keto/block/StorageManager.hpp"

namespace keto {
namespace block {

BlockModuleManager::BlockModuleManager() {
}

BlockModuleManager::~BlockModuleManager() {
}

// meta methods
const std::string BlockModuleManager::getName() const {
    return "BlockModuleManager";
}

const std::string BlockModuleManager::getDescription() const {
    return "The block module manager responsible for managing the block production.";
}

const std::string BlockModuleManager::getVersion() const {
    return keto::common::MetaInfo::VERSION;
}

// lifecycle methods
void BlockModuleManager::start() {
    StorageManager::init();
    modules["blockModule"] = std::make_shared<BlockModule>();
    KETO_LOG_INFO << "[BlockModuleManager] Started the BlockModuleManager";
}

void BlockModuleManager::stop() {
    modules.clear();
    StorageManager::fin();
    KETO_LOG_INFO << "[BlockModuleManager] The BlockModuleManager is being stopped";
}

const std::vector<std::string> BlockModuleManager::listModules() {
    std::vector<std::string> keys;
    std::transform(
        this->modules.begin(),
        this->modules.end(),
        std::back_inserter(keys),
        [](const std::map<std::string,std::shared_ptr<keto::module::ModuleInterface>>::value_type 
            &pair){return pair.first;});
    return keys;
}

const std::shared_ptr<keto::module::ModuleInterface> 
    BlockModuleManager::getModule(const std::string& name) {
    return modules[name];
}

boost::shared_ptr<BlockModuleManager> BlockModuleManager::create_module() {
    return boost::shared_ptr<BlockModuleManager>(new BlockModuleManager());    

}


BOOST_DLL_ALIAS(
    keto::block::BlockModuleManager::create_module,
    create_module
)


}
}
