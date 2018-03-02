/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HttpTransactionManager.hpp
 * Author: ubuntu
 *
 * Created on March 2, 2018, 7:11 AM
 */

#ifndef HTTPTRANSACTIONMANAGER_HPP
#define HTTPTRANSACTIONMANAGER_HPP


#include <string>
#include <memory>

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>

#include "keto/server_session/HttpSessionManager.hpp"

namespace keto {
namespace server_session {

class HttpTransactionManager {
public:
    HttpTransactionManager(std::shared_ptr<HttpSessionManager>& httpSessionManagerPtr);
    HttpTransactionManager(const HttpTransactionManager& orig) = delete;
    virtual ~HttpTransactionManager();
    
    std::string processTransaction(
            boost::beast::http::request<boost::beast::http::string_body>& req,
            const std::string& transactionMsg);
    
private:
    std::shared_ptr<HttpSessionManager> httpSessionManagerPtr;
};


}
}


#endif /* HTTPTRANSACTIONMANAGER_HPP */

