/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GenesisReader.cpp
 * Author: ubuntu
 * 
 * Created on March 8, 2018, 9:36 AM
 */

#include <iostream>

#include "keto/block/GenesisReader.hpp"

#include "keto/environment/EnvironmentManager.hpp"
#include "keto/environment/Config.hpp"
#include "include/keto/block/GenesisReader.hpp"


namespace keto {
namespace block {


GenesisReader::GenesisReader(const boost::filesystem::path& path) {
    std::ifstream ifs(path.string());
    nlohmann::json jsonData;
    ifs >> this->jsonData;
}

GenesisReader::~GenesisReader() {
}


nlohmann::json GenesisReader::getJsonData() {
    return this->jsonData;
}

}
}