/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HttpRequestManager.hpp
 * Author: ubuntu
 *
 * Created on February 15, 2018, 10:05 AM
 */

#ifndef HTTP_SERVER_REQUESTMANAGER_HPP
#define HTTP_SERVER_REQUESTMANAGER_HPP

#include <string>
#include <memory>

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>

#include "keto/common/HttpEndPoints.hpp"

#include "keto/server_session/HttpSessionManager.hpp"

namespace keto {
namespace server_session {

class HttpRequestManager {
public:
    HttpRequestManager(const HttpRequestManager& orig) = delete;
    virtual ~HttpRequestManager();
    
    static std::shared_ptr<HttpRequestManager> init();
    static void fin();
    static std::shared_ptr<HttpRequestManager> getInstance();
    
    bool checkRequest(boost::beast::http::request<boost::beast::http::string_body>& req);
    
    
    boost::beast::http::response<boost::beast::http::string_body>
    handle_request(boost::beast::http::request<boost::beast::http::string_body>& req);
    
private:
    std::shared_ptr<HttpSessionManager> httpSessionManagerPtr;
    
    HttpRequestManager();
    
    
    
};


}
}


#endif /* HTTPREQUESTMANAGER_HPP */

