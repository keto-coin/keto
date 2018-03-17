/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SignedChangeSetBuilder.cpp
 * Author: ubuntu
 * 
 * Created on March 17, 2018, 5:30 AM
 */

#include "keto/transaction_common/SignedChangeSetBuilder.hpp"
#include "keto/asn1/SerializationHelper.hpp"
#include "keto/crypto/SignatureGenerator.hpp"
#include "keto/crypto/HashGenerator.hpp"
#include "keto/asn1/HashHelper.hpp"
#include "keto/asn1/SignatureHelper.hpp"


namespace keto {
namespace transaction_common {


SignedChangeSetBuilder::SignedChangeSetBuilder() {
    this->signedChangedSet = (SignedChangeSet_t*)calloc(1, sizeof *signedChangedSet);
    
}

SignedChangeSetBuilder::SignedChangeSetBuilder(ChangeSet_t* changeSet) {
    this->signedChangedSet = (SignedChangeSet_t*)calloc(1, sizeof *signedChangedSet);
    keto::asn1::HashHelper hashHelper(
        keto::crypto::HashGenerator().generateHash(
        keto::asn1::SerializationHelper<ChangeSet_t>(changeSet,&asn_DEF_ChangeSet).operator std::vector<uint8_t>&()
        ));
    this->signedChangedSet->changeSet = *changeSet;
    free(changeSet);
    this->signedChangedSet->changeSetHash = hashHelper;
}

SignedChangeSetBuilder::SignedChangeSetBuilder(ChangeSet_t* changeSet, 
            const keto::crypto::KeyLoader& keyLoader) : keyLoader(keyLoader) {
    this->signedChangedSet = (SignedChangeSet_t*)calloc(1, sizeof *signedChangedSet);
    keto::asn1::HashHelper hashHelper(
        keto::crypto::HashGenerator().generateHash(
        keto::asn1::SerializationHelper<ChangeSet_t>(changeSet,&asn_DEF_ChangeSet).operator std::vector<uint8_t>&()
        ));
    this->signedChangedSet->changeSet = *changeSet;
    free(changeSet);
    this->signedChangedSet->changeSetHash = hashHelper;
}


SignedChangeSetBuilder::~SignedChangeSetBuilder() {
    if (signedChangedSet) {
        ASN_STRUCT_FREE(asn_DEF_SignedChangeSet, signedChangedSet);
        signedChangedSet = NULL;
    }
}

SignedChangeSetBuilder& SignedChangeSetBuilder::setChangeSet(ChangeSet_t* changeSet) {
    keto::asn1::HashHelper hashHelper(
        keto::crypto::HashGenerator().generateHash(
        keto::asn1::SerializationHelper<ChangeSet_t>(changeSet,&asn_DEF_ChangeSet).operator std::vector<uint8_t>&()
        ));
    this->signedChangedSet->changeSet = *changeSet;
    free(changeSet);
    this->signedChangedSet->changeSetHash = hashHelper;
    return (*this);
}

SignedChangeSetBuilder& SignedChangeSetBuilder::setKeyLoader(
        const keto::crypto::KeyLoader& keyloader) {
    this->keyLoader = keyLoader;
    return (*this);
}

SignedChangeSetBuilder& SignedChangeSetBuilder::sign() {
    keto::crypto::SignatureGenerator generator(this->keyLoader);
    keto::asn1::HashHelper hashHelper(this->signedChangedSet->changeSetHash);
    keto::asn1::SignatureHelper signatureHelper(generator.sign(hashHelper));
    this->signedChangedSet->signature = signatureHelper;
    return (*this);
}

SignedChangeSetBuilder::operator SignedChangeSet_t*() {
    SignedChangeSet_t* result = this->signedChangedSet;
    this->signedChangedSet = 0;
    return result;
}

SignedChangeSetBuilder::operator SignedChangeSet_t&() {
    return *this->signedChangedSet;
}


}
}