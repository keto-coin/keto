/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AccountStatementBuilder.hpp
 * Author: ubuntu
 *
 * Created on March 20, 2018, 11:54 AM
 */

#ifndef ACCOUNTSTATEMENTBUILDER_HPP
#define ACCOUNTSTATEMENTBUILDER_HPP

#include <string>
#include <memory>

#include <librdf.h>
#include <redland.h>
#include <rdf_storage.h>
#include <rdf_model.h>


namespace keto {
namespace account_db {

class AccountRDFStatementBuilder;
typedef std::shared_ptr<AccountRDFStatementBuilder> AccountRDFStatementBuilderPtr;

class AccountRDFStatementBuilder {
public:
    AccountRDFStatementBuilder(const ChangeSet_t& changeSet);
    AccountRDFStatementBuilder(const AccountRDFStatementBuilder& orig) = delete;
    virtual ~AccountRDFStatementBuilder();
    
    
    
    
    
private:
    ChangeSet_t changeSet;
};


}
}

#endif /* ACCOUNTSTATEMENTBUILDER_HPP */

