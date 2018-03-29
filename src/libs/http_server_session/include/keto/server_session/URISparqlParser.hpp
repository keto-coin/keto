/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   URISparqlParser.hpp
 * Author: ubuntu
 *
 * Created on March 29, 2018, 6:19 AM
 */

#ifndef URISPARQLPARSER_HPP
#define URISPARQLPARSER_HPP

#include <string>


namespace keto {
namespace server_session {
        
class URISparqlParser {
public:
    
    static constexpr const char* QUERY_PARAM = "query=";
    
    URISparqlParser(const std::string& uri, const std::string& body);
    URISparqlParser(const URISparqlParser& orig) = default;
    virtual ~URISparqlParser();
    
    std::string getAccountHash();
    std::string getQuery();
    
    
private:
    std::string accountHash;
    std::string query;
    
};


}
}


#endif /* URISPARQLPARSER_HPP */

