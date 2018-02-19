/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HttpSession.hpp
 * Author: ubuntu
 *
 * Created on February 19, 2018, 11:07 AM
 */

#ifndef KETO_HTTPSESSION_HPP
#define KETO_HTTPSESSION_HPP

#include <chrono>
#include <map>
#include <vector>

#include "keto/crypto/Containers.hpp"


namespace keto {
namespace server_session {


class HttpSession {
public:
    HttpSession(const std::vector<uint8_t>& clientHash);
    HttpSession(const HttpSession& orig) = delete;
    virtual ~HttpSession();
    
    std::vector<uint8_t> getClientHash();
    std::vector<uint8_t> getSessionHash();
    keto::crypto::SecureVector getSessionKey();
    
    std::chrono::system_clock::time_point getCreateTime();
    std::chrono::system_clock::time_point getTouchTime();
    
    
private:
    std::vector<uint8_t> clientHash;
    std::vector<uint8_t> sessionHash;
    keto::crypto::SecureVector sessionKey;
    std::chrono::system_clock::time_point createTime;
    std::chrono::system_clock::time_point touchTime;
    
    
    void touch();
};


}
}

#endif /* HTTPSESSION_HPP */

