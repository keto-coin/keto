/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ServerInfo.hpp
 * Author: ubuntu
 *
 * Created on February 16, 2018, 8:31 AM
 */

#ifndef KETO_SERVER_COMMON_SERVERINFO_HPP
#define KETO_SERVER_COMMON_SERVERINFO_HPP

#include <memory>
#include <vector>

#include <boost/filesystem/path.hpp>

namespace keto {
namespace server_common {

class ServerInfo {
public:
    ServerInfo(const ServerInfo& orig) = delete;
    virtual ~ServerInfo();
    
    // singleton methods
    static std::shared_ptr<ServerInfo> getInstance();
    
    /**
     * This method returns the account hash
     * 
     * @return The hash bytes
     */
    std::vector<uint8_t> getAccountHash();
    
    /**
     * This method returns the public key directory path. This contains all the
     * public keys registered with the keto server.
     * 
     * @return The path to the public key path.
     */
    boost::filesystem::path getPublicKeyPath();
    
private:
    std::vector<uint8_t> accountHash;
    boost::filesystem::path publicKeyPath;
    
    ServerInfo();
    
    
};


}
}


#endif /* SERVERINFO_HPP */

