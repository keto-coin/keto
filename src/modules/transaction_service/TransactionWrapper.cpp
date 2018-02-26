/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TransactionWrapper.cpp
 * Author: ubuntu
 * 
 * Created on February 26, 2018, 12:53 PM
 */

#include <vector>

#include "keto/transaction/TransactionWrapper.hpp"
#include "include/keto/transaction/TransactionWrapper.hpp"

namespace keto {
namespace transaction {

TransactionWrapper::TransactionWrapper() {
}

TransactionWrapper::~TransactionWrapper() {
}

void TransactionWrapper::commit() {
    for (Resource* resource : this->resources) {
        resource->commit();
    }
    this->resources.clear();
}

void TransactionWrapper::rollback() {
    for (Resource* resource : this->resources) {
        resource->rollback();
    }
    this->resources.clear();
}
    
void TransactionWrapper::enlist(Resource& resource) {
    this->resources.push_back(&resource);
}
    

}
}
