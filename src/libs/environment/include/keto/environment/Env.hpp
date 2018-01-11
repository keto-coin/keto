/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   evw.hpp
 * Author: ubuntu
 *
 * Created on January 10, 2018, 3:33 PM
 */

#ifndef ENV_HPP
#define ENV_HPP

#include <string>

namespace keto {
namespace environment {

class Env {
public:
    Env();
    virtual ~Env();
    Env(const Env& origin) = delete;

    std::string getInstallDir();

private:
    std::string installDir;
};

} 
}

#endif /* EVW_HPP */

