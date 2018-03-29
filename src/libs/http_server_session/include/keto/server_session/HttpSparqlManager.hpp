/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HttpSparqlManager.hpp
 * Author: ubuntu
 *
 * Created on March 28, 2018, 11:02 AM
 */

#ifndef HTTPSPARQLMANAGER_HPP
#define HTTPSPARQLMANAGER_HPP

#include <string>
#include <memory>

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>

#include "keto/server_session/HttpSessionManager.hpp"

namespace keto {
namespace server_session {


class HttpSparqlManager {
public:
    HttpSparqlManager(std::shared_ptr<HttpSessionManager>& httpSessionManagerPtr);
    HttpSparqlManager(const HttpSparqlManager& orig) = delete;
    virtual ~HttpSparqlManager();
    
    std::string processQuery(
            boost::beast::http::request<boost::beast::http::string_body>& req,
            const std::string& body);
    
private:
    std::shared_ptr<HttpSessionManager> httpSessionManagerPtr;
};

}
}

#endif /* HTTPSPARQLMANAGER_HPP */

