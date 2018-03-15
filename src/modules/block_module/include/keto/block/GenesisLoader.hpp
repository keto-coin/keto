/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GenesisLoader.hpp
 * Author: ubuntu
 *
 * Created on March 8, 2018, 10:02 AM
 */

#ifndef GENESISLOADER_HPP
#define GENESISLOADER_HPP

#include <memory>

#include "keto/block/GenesisReader.hpp"
#include "keto/crypto/KeyLoader.hpp"

namespace keto {
namespace block {

class GenesisLoader {
public:
    GenesisLoader(const GenesisReader& reader);
    GenesisLoader(const GenesisLoader& orig);
    virtual ~GenesisLoader();
    
    void load();
    
private:
    GenesisReader reader;
    std::shared_ptr<keto::crypto::KeyLoader> keyLoaderPtr;
    
};


}
}


#endif /* GENESISLOADER_HPP */

