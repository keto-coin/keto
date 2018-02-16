/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   KeyLoader.cpp
 * Author: ubuntu
 * 
 * Created on February 14, 2018, 7:04 AM
 */

#include <boost/filesystem/path.hpp>

#include <botan/pkcs8.h>
#include <botan/hash.h>
#include <botan/data_src.h>
#include <botan/pubkey.h>
#include <botan/rng.h>
#include <botan/auto_rng.h>

#include "keto/crypto/Exception.hpp"
#include "keto/crypto/KeyLoader.hpp"
#include "keto/environment/EnvironmentManager.hpp"
#include "include/keto/crypto/KeyLoader.hpp"

namespace keto {
namespace crypto {

KeyLoader::KeyLoader() : initialized(false), generator(new Botan::AutoSeeded_RNG()) {
    
}

KeyLoader::KeyLoader(const boost::filesystem::path& publicKeyPath) : initialized(true),
        publicKeyPath(publicKeyPath.string()), generator(new Botan::AutoSeeded_RNG())
{
}

KeyLoader::KeyLoader(const std::string& publicKeyPath) : initialized(true),
        publicKeyPath(publicKeyPath), generator(new Botan::AutoSeeded_RNG())
{
    // setup the paths using the environmental variables
    boost::filesystem::path publicPath =  
            keto::environment::EnvironmentManager::getInstance()->getEnv()->getInstallDir() / publicKeyPath;
    if (!publicPath.is_complete()) {
        BOOST_THROW_EXCEPTION(keto::crypto::InvalidKeyPathException());
    }
    this->publicKeyPath = publicPath.string();
}
    
    
KeyLoader::KeyLoader(const std::string& privateKeyPath, 
        const std::string& publicKeyPath) : initialized(true), 
        privateKeyPath(privateKeyPath), publicKeyPath(publicKeyPath),
        generator(new Botan::AutoSeeded_RNG())
{
    
    // setup the paths using the environmental variables
    boost::filesystem::path publicPath =  
            keto::environment::EnvironmentManager::getInstance()->getEnv()->getInstallDir() / publicKeyPath;
    if (!publicPath.is_complete()) {
        BOOST_THROW_EXCEPTION(keto::crypto::InvalidKeyPathException());
    }
    this->publicKeyPath = publicPath.string();
    
    // setup the paths using the environmental variables
    boost::filesystem::path privatePath =  
            keto::environment::EnvironmentManager::getInstance()->getEnv()->getInstallDir() / privateKeyPath;
    if (!privatePath.is_complete()) {
        BOOST_THROW_EXCEPTION(keto::crypto::InvalidKeyPathException());
    }
    this->privateKeyPath = privatePath.string();
}

KeyLoader::~KeyLoader() {
}

std::shared_ptr<Botan::Private_Key> KeyLoader::getPrivateKey() {
    if (!isInitialized()) {
        BOOST_THROW_EXCEPTION(keto::crypto::KeyLoaderNotInitializedException());
    }
    if (this->privateKeyPath.empty()) {
        BOOST_THROW_EXCEPTION(keto::crypto::PrivateKeyNotConfiguredException());
    }
    // attempt to load the private key using the path supplied and the 
    return std::shared_ptr<Botan::Private_Key>(
            Botan::PKCS8::load_key(this->privateKeyPath, *generator));
}


std::shared_ptr<Botan::Public_Key> KeyLoader::getPublicKey() {
    if (!isInitialized()) {
        BOOST_THROW_EXCEPTION(keto::crypto::KeyLoaderNotInitializedException());
    }
    if (this->privateKeyPath.empty()) {
        BOOST_THROW_EXCEPTION(keto::crypto::PrivateKeyNotConfiguredException());
    }
    // attempt to load the private key using the path supplied and the 
    return std::shared_ptr<Botan::Public_Key>(
            Botan::X509::load_key(this->publicKeyPath));
}

bool KeyLoader::isInitialized() {
    return this->initialized;
}
    

}
}
