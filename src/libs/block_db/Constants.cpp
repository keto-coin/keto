/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "keto/block_db/Constants.hpp"


namespace keto {
namespace block_db {

    
const char* Constants::BLOCKS_INDEX = "blocks";
const char* Constants::TRANSACTIONS_INDEX = "transactions";
const char* Constants::ACCOUNTS_INDEX = "accounts";

const char* Constants::BOOT_KEY     = "boot_key";
const char* Constants::BOOT_VALUE   = "booted";

const std::vector<std::string> Constants::DB_LIST = 
    {Constants::BLOCKS_INDEX,Constants::TRANSACTIONS_INDEX,Constants::ACCOUNTS_INDEX};
    
}
}

