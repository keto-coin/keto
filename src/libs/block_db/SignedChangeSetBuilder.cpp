/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SignedChangeSetBuilder.cpp
 * Author: ubuntu
 * 
 * Created on March 13, 2018, 1:56 PM
 */

#include "keto/block_db/SignedChangeSetBuilder.hpp"

#include "keto/asn1/SerializationHelper.hpp"
#include "keto/asn1/BerEncodingHelper.hpp"
#include "keto/crypto/SignatureGenerator.hpp"
#include "keto/crypto/HashGenerator.hpp"
#include "keto/block_db/SignedChangeSetBuilder.hpp"


namespace keto {
namespace block_db {


SignedChangeSetBuilder::SignedChangeSetBuilder() {
}

SignedChangeSetBuilder::SignedChangeSetBuilder(
            const keto::asn1::PrivateKeyHelper& privateKeyHelper,
            keto::asn1::ChangeSetHelper& changeSetHelper) : 
    privateKeyHelper(privateKeyHelper) {
    this->changeSet = (ChangeSet_t*)changeSetHelper;
}

SignedChangeSetBuilder::~SignedChangeSetBuilder() {
    if (this->changeSet) {
        ASN_STRUCT_FREE(asn_DEF_ChangeSet, this->changeSet);
        this->changeSet = 0;
    }
}

SignedChangeSetBuilder& SignedChangeSetBuilder::setPrivateKey(
        const keto::asn1::PrivateKeyHelper& privateKeyHelper) {
    this->privateKeyHelper = privateKeyHelper;
    return (*this);
}

SignedChangeSetBuilder& SignedChangeSetBuilder::setChangeSet(
        keto::asn1::ChangeSetHelper& changeSetHelper) {
    this->changeSet = (ChangeSet_t*)changeSetHelper;
    return (*this);
}

SignedChangeSetBuilder::operator SignedChangeSet_t*() {
    
    SignedChangeSet_t* signedChangeSet = 0;
    try {
        signedChangeSet = (SignedChangeSet_t*)calloc(1, sizeof *signedChangeSet);
        signedChangeSet->changeSet = *changeSet;
        keto::asn1::HashHelper hashHelper = getHash();
        signedChangeSet->changeSetHash = hashHelper;
        keto::asn1::BerEncodingHelper key = this->privateKeyHelper.getKey();
        keto::crypto::SignatureGenerator generator((keto::crypto::SecureVector)key);
        keto::asn1::SignatureHelper signatureHelper(generator.sign(hashHelper));
        signedChangeSet->signature = signatureHelper;
    } catch (...) {
        if (signedChangeSet) {
            free(signedChangeSet);
        }
        throw;
    }
    free(changeSet);
    changeSet = 0;
    return signedChangeSet;
}

keto::asn1::HashHelper SignedChangeSetBuilder::getHash() {
    keto::asn1::SerializationHelper<ChangeSet_t> serializationHelper(changeSet, &asn_DEF_ChangeSet);
    return keto::asn1::HashHelper(
        keto::crypto::HashGenerator().generateHash(
        serializationHelper.operator std::vector<uint8_t>&()));
}

}
}