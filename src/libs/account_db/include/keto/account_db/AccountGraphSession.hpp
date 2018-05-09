/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AccountGraphSession.hpp
 * Author: ubuntu
 *
 * Created on March 28, 2018, 6:00 AM
 */

#ifndef ACCOUNTGRAPHSESSION_HPP
#define ACCOUNTGRAPHSESSION_HPP

#include <memory>
#include <string>
#include <vector>
#include <map>

#include <librdf.h>
#include <redland.h>
#include <rdf_storage.h>
#include <rdf_model.h>

#include "keto/account_db/AccountGraphStore.hpp"
#include "keto/asn1/RDFSubjectHelper.hpp"

namespace keto {
namespace account_db {

class AccountGraphSession;
typedef std::shared_ptr<AccountGraphSession> AccountGraphSessionPtr;
typedef std::map<std::string,std::string> ResultMap;
typedef std::vector<ResultMap> ResultVectorMap;
    
class AccountGraphSession {
public:
    friend class AccountResource;
    AccountGraphSession(const AccountGraphSession& orig) = delete;
    virtual ~AccountGraphSession();
    
    void persist(keto::asn1::RDFSubjectHelperPtr& subject);
    void remove(keto::asn1::RDFSubjectHelperPtr& subject);
    std::string query(const std::string& query);
    ResultVectorMap executeQuery(const std::string& queryStr);
    
protected:
    AccountGraphSession(const AccountGraphStorePtr& accountGraphStore);
    
    void commit();
    void rollback();
    
private:
    bool activeTransaction;
    AccountGraphStorePtr accountGraphStore;
    
    // transaction methods
    
};

        
}
}

#endif /* ACCOUNTGRAPHSESSION_HPP */

