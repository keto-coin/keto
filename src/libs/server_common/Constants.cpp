/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Constants.cpp
 * Author: ubuntu
 * 
 * Created on February 16, 2018, 8:18 AM
 */

#include "keto/server_common/Constants.hpp"

namespace keto {
namespace server_common {


const char* Constants::PUBLIC_KEY_DIR = "public-key-dir";
const char* Constants::ACCOUNT_HASH = "account-hash";

const char* Constants::SERVICE::ROUTE       = "route";
const char* Constants::SERVICE::BALANCE     = "balance";
const char* Constants::SERVICE::BLOCK       = "block";
const char* Constants::SERVICE::PROCESS     = "process";

}
}