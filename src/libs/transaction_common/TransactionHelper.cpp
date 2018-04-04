/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TransactionHelper.cpp
 * Author: ubuntu
 * 
 * Created on April 3, 2018, 10:40 AM
 */

#include "keto/transaction_common/TransactionHelper.hpp"

namespace keto {
namespace transaction_common {

TransactionHelper::TransactionHelper(Transaction* transaction) : 
    transaction(transaction) {
}

TransactionHelper::~TransactionHelper() {
}

long TransactionHelper::getVersion() {
    return transaction->version;
}

keto::asn1::NumberHelper TransactionHelper::getValue() {
    return transaction->value;
}

keto::asn1::HashHelper TransactionHelper::getParent() {
    return transaction->parent;
}

keto::asn1::TimeHelper TransactionHelper::getDate() {
    return transaction->date;
}

keto::asn1::HashHelper TransactionHelper::getSourceAccount() {
    return transaction->sourceAccount;
}

keto::asn1::HashHelper TransactionHelper::getTargetAccount() {
    return transaction->targetAccount;
}

std::vector<ActionHelperPtr> TransactionHelper::getActions() {
    std::vector<ActionHelperPtr> result;
    for (int index = 0; index < transaction->actions.list.count; index++) {
        result.push_back(ActionHelperPtr(new ActionHelper(transaction->actions.list.array[index])));
    }
    return result;
}


}
}