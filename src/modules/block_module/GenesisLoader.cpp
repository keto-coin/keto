/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GenesisLoader.cpp
 * Author: ubuntu
 * 
 * Created on March 8, 2018, 10:02 AM
 */

#include "keto/block/GenesisLoader.hpp"

namespace keto {
namespace block {

GenesisLoader::GenesisLoader(const GenesisReader& reader) : reader(reader) {
}

GenesisLoader::GenesisLoader(const GenesisLoader& orig) : reader(orig.reader) {
}

GenesisLoader::~GenesisLoader() {
}

void GenesisLoader::load() {
    
}

}
}
