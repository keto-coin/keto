/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RDFConstants.cpp
 * Author: ubuntu
 * 
 * Created on May 16, 2018, 6:08 AM
 */

#include "keto/wavm_common/RDFConstants.hpp"

namespace keto {
namespace wavm_common {

const char* RDFConstants::ACCOUNT_TRANSACTION_SUBJECTS::ID = "id";
const char* RDFConstants::ACCOUNT_TRANSACTION_SUBJECTS::ACCOUNT_HASH = "accountHash";
const char* RDFConstants::ACCOUNT_TRANSACTION_SUBJECTS::TYPE = "type";
const char* RDFConstants::ACCOUNT_TRANSACTION_SUBJECTS::DATE_TIME = "dateTime";
const char* RDFConstants::ACCOUNT_TRANSACTION_SUBJECTS::VALUE = "value";

const char* RDFConstants::TYPES::STRING = "http://www.w3.org/2001/XMLSchema#string";
const char* RDFConstants::TYPES::LONG = "http://www.w3.org/2001/XMLSchema#decimal";
const char* RDFConstants::TYPES::FLOAT = "http://www.w3.org/2001/XMLSchema#float";
const char* RDFConstants::TYPES::BOOLEAN = "http://www.w3.org/2001/XMLSchema#Boolean";
const char* RDFConstants::TYPES::DATE_TIME = "http://www.w3.org/2001/XMLSchema#dateTime";

const char* RDFConstants::NODE_TYPES::LITERAL = "literal";

}
}