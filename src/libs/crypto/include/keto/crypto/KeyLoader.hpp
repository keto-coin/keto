/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   KeyLoader.hpp
 * Author: ubuntu
 *
 * Created on February 14, 2018, 7:04 AM
 */

#ifndef KEYLOADER_HPP
#define KEYLOADER_HPP

#include <string>
#include <memory>

#include <boost/filesystem/path.hpp>

#include <botan/pkcs8.h>
#include <botan/x509_key.h>
#include <botan/pubkey.h>
#include <botan/rng.h>
#include <botan/auto_rng.h>



namespace keto {
namespace crypto {


class KeyLoader {
public:
    KeyLoader();
    KeyLoader(const std::string& publicKeyPath);
    KeyLoader(const boost::filesystem::path& publicKeyPath);
    KeyLoader(const std::string& privateKeyPath, const std::string& publicKeyPath);
    KeyLoader(const KeyLoader& orig) = default;
    virtual ~KeyLoader();
    
    std::shared_ptr<Botan::Private_Key> getPrivateKey();
    std::shared_ptr<Botan::Public_Key> getPublicKey();
    
    bool isInitialized();
    
private:
    bool initialized;
    std::string privateKeyPath;
    std::string publicKeyPath;
    std::shared_ptr<Botan::AutoSeeded_RNG> generator;
};

}
}

#endif /* KEYLOADER_HPP */

