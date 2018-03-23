/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AccountRDFStatement.cpp
 * Author: ubuntu
 * 
 * Created on March 21, 2018, 5:50 PM
 */

#include "RDFModel.h"

#include "keto/asn1/AnyHelper.hpp"
#include "keto/account_db/AccountRDFStatement.hpp"
#include "keto/account_db/Exception.hpp"
#include "include/keto/account_db/RDFDBOperation.hpp"
#include "include/keto/account_db/AccountRDFStatement.hpp"


namespace keto {
namespace account_db {

AccountRDFStatement::AccountRDFStatement(ChangeData* changeData) {
    if (changeData->present != ChangeData_PR_asn1Change) {
        BOOST_THROW_EXCEPTION(keto::account_db::UnsupportedChangeTypeFormatException());
    }
    rdfModelHelper = keto::asn1::RDFModelHelperPtr(new keto::asn1::RDFModelHelper(
        keto::asn1::AnyHelper(changeData->choice.asn1Change).
            extract<RDFModel_t>(&asn_DEF_RDFModel)));
}
        

AccountRDFStatement::~AccountRDFStatement() {
}

RDFDBOperation AccountRDFStatement::getOperation() {
    if (this->rdfModelHelper->operator RDFModel_t&().action == RDFChange_persist) {
        return keto::account_db::PERSIST;
    } else {
        return keto::account_db::REMOVE;
    }
}

keto::asn1::RDFModelHelperPtr AccountRDFStatement::getModel() {
    return this->rdfModelHelper;
}


}
}