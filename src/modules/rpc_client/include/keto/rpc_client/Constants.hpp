/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Constants.hpp
 * Author: ubuntu
 *
 * Created on January 22, 2018, 3:36 PM
 */

#ifndef RPC_CLIENT_CONSTANTS_HPP
#define RPC_CLIENT_CONSTANTS_HPP

namespace keto {
namespace rpc_client {


class Constants {
public:
    Constants() = delete;
    Constants(const Constants& orig) = delete;
    virtual ~Constants() = delete;
    
    static constexpr const char* DEFAULT_PORT_NUMBER = "28003";
    
    static constexpr const char* PEERS = "rpc-peer";
    
    static constexpr const char* PEER_HELLO = "HELLO";
    
    static constexpr const char* RPC_CLIENT_THREADS = "rpc-server-thread-number";
    static constexpr const int DEFAULT_RPC_CLIENT_THREADS = 1;
};

}
}

#endif /* CONSTANTS_HPP */

