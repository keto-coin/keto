/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MerkleUtils.hpp
 * Author: ubuntu
 *
 * Created on March 14, 2018, 7:02 AM
 */

#ifndef MERKLEUTILS_HPP
#define MERKLEUTILS_HPP

#include <string>
#include <vector>

#include "Block.h"

#include "SignedTransaction.h"
#include "keto/asn1/HashHelper.hpp"
#include "keto/block_db/SignedChangeSetBuilder.hpp"

namespace keto {
namespace block_db {


class MerkleUtils {
public:
    MerkleUtils(const Block_t* block);
    MerkleUtils(const MerkleUtils& orig) = default;
    virtual ~MerkleUtils();
    
    keto::asn1::HashHelper computation(/*
            const std::vector<uint256>& leaves,
            uint256* proot,
            bool* pmutated,
            uint32_t branchpos,
            std::vector<uint256>* pbranch*/);
private:
    std::vector<keto::asn1::HashHelper> hashs;
    
    keto::asn1::HashHelper compute(std::vector<keto::asn1::HashHelper> hashs);
    keto::asn1::HashHelper compute(keto::asn1::HashHelper lhs, keto::asn1::HashHelper rhs);
};

}
}

#endif /* MERKLEUTILS_HPP */

