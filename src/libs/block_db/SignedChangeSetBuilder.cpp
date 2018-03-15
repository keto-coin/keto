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
#include "keto/block_db/Exception.hpp"


namespace keto {
namespace block_db {


SignedChangeSetBuilder::SignedChangeSetBuilder() {
    signedChangeSet = (SignedChangeSet_t*)calloc(1, sizeof *signedChangeSet);
}

SignedChangeSetBuilder::SignedChangeSetBuilder(
            const keto::asn1::PrivateKeyHelper& privateKeyHelper,
            keto::asn1::ChangeSetHelper& changeSetHelper) : 
    privateKeyHelper(privateKeyHelper) {
    signedChangeSet = (SignedChangeSet_t*)calloc(1, sizeof *signedChangeSet);
    ChangeSet_t* changeSet = changeSetHelper;
    signedChangeSet->changeSet = *changeSet;
    signedChangeSet->changeSetHash = this->getChangeSetHash(changeSet);
    free(changeSet);
}

SignedChangeSetBuilder::~SignedChangeSetBuilder() {
    if (this->signedChangeSet) {
        ASN_STRUCT_FREE(asn_DEF_SignedChangeSet, this->signedChangeSet);
        this->signedChangeSet = 0;
    }
}

SignedChangeSetBuilder& SignedChangeSetBuilder::setPrivateKey(
        const keto::asn1::PrivateKeyHelper& privateKeyHelper) {
    this->privateKeyHelper = privateKeyHelper;
    return (*this);
}

SignedChangeSetBuilder& SignedChangeSetBuilder::setChangeSet(
        keto::asn1::ChangeSetHelper& changeSetHelper) {
    ChangeSet_t* changeSet = changeSetHelper;
    signedChangeSet->changeSet = *changeSet;
    signedChangeSet->changeSetHash = this->getChangeSetHash(changeSet);
    free(changeSet);
    return (*this);
}


SignedChangeSetBuilder& SignedChangeSetBuilder::sign() {
    if (!this->signedChangeSet) {
        BOOST_THROW_EXCEPTION(keto::block_db::SignedChangeSetReleasedException());
    }
    keto::asn1::BerEncodingHelper key = this->privateKeyHelper.getKey();
    keto::crypto::SignatureGenerator generator((keto::crypto::SecureVector)key);
    keto::asn1::HashHelper hashHelper(this->signedChangeSet->changeSetHash);
    keto::asn1::SignatureHelper signatureHelper(generator.sign(hashHelper));
    signedChangeSet->signature = signatureHelper;
    return (*this);
}

SignedChangeSetBuilder::operator SignedChangeSet_t*() {
    SignedChangeSet_t* result = this->signedChangeSet;
    this->signedChangeSet = 0;
    
    // return the new signed change set
    return result;
}

keto::asn1::HashHelper SignedChangeSetBuilder::getHash() {
    if (!this->signedChangeSet) {
        BOOST_THROW_EXCEPTION(keto::block_db::SignedChangeSetReleasedException());
    }
    return this->signedChangeSet->changeSetHash;
}

keto::asn1::HashHelper SignedChangeSetBuilder::getChangeSetHash(ChangeSet_t* changeSet) {
    keto::asn1::SerializationHelper<ChangeSet_t> serializationHelper(changeSet, &asn_DEF_ChangeSet);
    return keto::asn1::HashHelper(
        keto::crypto::HashGenerator().generateHash(
        serializationHelper.operator std::vector<uint8_t>&()));
}

}
}