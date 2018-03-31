/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ServiceRegistryHelper.hpp
 * Author: ubuntu
 *
 * Created on March 31, 2018, 4:45 AM
 */

#ifndef SERVICEREGISTRYHELPER_HPP
#define SERVICEREGISTRYHELPER_HPP

#include <string>

namespace keto {
namespace server_common {
    
void registerService(const std::string& service);

}
}


#endif /* SERVICEREGISTRYHELPER_HPP */

