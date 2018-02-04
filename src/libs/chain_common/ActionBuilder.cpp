/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ActionBuilder.cpp
 * Author: ubuntu
 * 
 * Created on February 3, 2018, 10:16 AM
 */

#include "keto/chain_common/ActionBuilder.hpp"
#include "keto/common/MetaInfo.hpp"
#include "keto/asn1/TimeHelper.hpp"


namespace keto {
namespace chain_common {


ActionBuilder::ActionBuilder() {
    this->action = (Action*)calloc(1, sizeof *action);
    this->action->version = keto::common::MetaInfo::PROTOCOL_VERSION;
    this->action->date = (UTCTime_t)keto::asn1::TimeHelper();
}

ActionBuilder::~ActionBuilder() {
    if (this->action) {
        ASN_STRUCT_FREE(asn_DEF_Action, this->action);
    }
}

std::shared_ptr<ActionBuilder> ActionBuilder::createAction() {
    return std::shared_ptr<ActionBuilder>(new ActionBuilder());
}

long ActionBuilder::getVersion() {
    return this->action->version;
}

keto::asn1::TimeHelper ActionBuilder::getDate() {
    return this->action->date;
}


ActionBuilder& ActionBuilder::setDate(const keto::asn1::TimeHelper& date) {
    this->action->date = date;
    return (*this);
}


keto::asn1::HashHelper ActionBuilder::getContract() {
    return this->action->contract;
}


ActionBuilder& ActionBuilder::setContract(const keto::asn1::HashHelper& contract) {
    this->action->contract = contract;
    return (*this);
}


keto::asn1::HashHelper ActionBuilder::getSourceAccount() {
    return this->action->sourceAccount;
}


ActionBuilder& ActionBuilder::setSourceAccount(const keto::asn1::HashHelper& sourceAccount) {
    this->action->sourceAccount = sourceAccount;
    return (*this);
}

keto::asn1::HashHelper ActionBuilder::getTargetAccount() {
    return this->action->targetAccount;
}


ActionBuilder& ActionBuilder::setTargetAccount(const keto::asn1::HashHelper& targetAccount) {
    this->action->targetAccount = targetAccount;
    return (*this);
}

keto::asn1::NumberHelper ActionBuilder::getValue() {
    return this->action->value;
}


ActionBuilder& ActionBuilder::setValue(const keto::asn1::NumberHelper& value) {
    this->action->value = value;
    return (*this);
}


keto::asn1::HashHelper ActionBuilder::getParent() {
    return this->action->parent;
}


ActionBuilder& ActionBuilder::setParent(const keto::asn1::HashHelper& parent) {
    this->action->parent = parent;
    return (*this);
}


keto::asn1::AnyHelper ActionBuilder::getModel() {
    return &this->action->model;
}


ActionBuilder& ActionBuilder::setModel(keto::asn1::AnyHelper& anyHelper) {
    this->action->model = (ANY_t)anyHelper;
    return (*this);
}

void* ActionBuilder::getPtr() {
    return this->action;
}

struct asn_TYPE_descriptor_s* ActionBuilder::getType() {
    return &asn_DEF_Action;
}

Action* ActionBuilder::takePtr() {
    Action* result = this->action;
    this->action = 0;
    return result;
}

}
}