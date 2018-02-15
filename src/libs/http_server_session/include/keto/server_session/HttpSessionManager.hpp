/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HttpSessionManager.hpp
 * Author: ubuntu
 *
 * Created on February 15, 2018, 9:39 AM
 */

#ifndef HTTP_SERVER_SESSIONMANAGER_HPP
#define HTTP_SERVER_SESSIONMANAGER_HPP

#include <string>
#include <memory>

#include "keto/server_session/HttpSessionManager.hpp"

namespace keto {
namespace server_session {

class HttpSessionManager {
public:
    friend class HttpRequestManager;
    
    HttpSessionManager();
    HttpSessionManager(const HttpSessionManager& orig) = delete;
    virtual ~HttpSessionManager();
    
    std::string processHello(const std::string& hello);
    
    
    
protected:
    
    
};


}
}


#endif /* HTTPSESSIONMANAGER_HPP */

