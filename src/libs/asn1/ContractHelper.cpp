/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ContractHelper.cpp
 * Author: ubuntu
 * 
 * Created on May 8, 2018, 6:35 AM
 */

#include "keto/asn1/ContractHelper.hpp"
#include "keto/common/MetaInfo.hpp"
#include "keto/asn1/CloneHelper.hpp"
#include "keto/asn1/DeserializationHelper.hpp"
#include "keto/asn1/Exception.hpp"

namespace keto {
namespace asn1 {


ContractHelper::ContractHelper() {
    this->contract = (Contract_t*)calloc(1, sizeof *this->contract);
    this->contract->version = keto::common::MetaInfo::PROTOCOL_VERSION;
}

ContractHelper::ContractHelper(const Contract_t& contract) {
    this->contract = 
            keto::asn1::clone<Contract_t>(&contract,&asn_DEF_Contract);
}

ContractHelper::ContractHelper(const std::string& contract) {
    DeserializationHelper<Contract_t> deserializer(
        (const unsigned char*)contract.data(),contract.size(),
            &asn_DEF_Contract);
    this->contract = deserializer.takePtr();
}

ContractHelper::ContractHelper(const ContractHelper& orig) {
    this->contract = 
            keto::asn1::clone<Contract_t>(orig.contract,&asn_DEF_Contract);
}

ContractHelper::~ContractHelper() {
    if (this->contract) {
        ASN_STRUCT_FREE(asn_DEF_Contract, this->contract);
    }
}

ContractHelper& ContractHelper::setId(const HashHelper& id) {
    this->contract->id = id;
    return *this;
}

HashHelper ContractHelper::getId() {
    return this->contract->id;
}

ContractHelper& ContractHelper::setName(const std::string& name) {
    OCTET_STRING_fromBuf(&contract->name,
            name.c_str(),name.size());
    return *this;
}

std::string ContractHelper::getName() {
    return std::string((const char*)this->contract->name.buf);
}

ContractHelper& ContractHelper::setOwner(const HashHelper& owner) {
    this->contract->owner = owner;
    return *this;
}

HashHelper ContractHelper::getOwner() {
    return this->contract->owner;
}

ContractHelper& ContractHelper::setPermissions(const std::vector<HashHelper>& permissions) {
    for (HashHelper permission : permissions) {
        Hash_t hashT = permission.operator Hash_t();
        if (0!= ASN_SEQUENCE_ADD(&this->contract->permissions,&hashT)) {
            BOOST_THROW_EXCEPTION(keto::asn1::FailedToAddPermission());
        }
    }
    return *this;
}

std::vector<HashHelper> ContractHelper::getPermissions() {
    std::vector<HashHelper> result;
    for (int index = 0; index < this->contract->permissions.list.count; index++) {
        result.push_back(HashHelper(*this->contract->permissions.list.array[index]));
    }
    return result;
}

ContractHelper& ContractHelper::setCode(const std::string& code) {
    OCTET_STRING_fromBuf(&contract->code,
            code.c_str(),code.size());
    return *this;
}

std::string ContractHelper::getCode() {
    return std::string((const char*)this->contract->code.buf);
}

ContractHelper::operator Contract*() {
    return keto::asn1::clone<Contract_t>(contract,&asn_DEF_Contract);
}

ContractHelper& ContractHelper::operator=(const Contract& contract) {
    this->contract = 
            keto::asn1::clone<Contract_t>(&contract,&asn_DEF_Contract);
    return *this;
}


}
}