/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestModule.h
 * Author: ubuntu
 *
 * Created on January 18, 2018, 10:28 AM
 */

#ifndef TESTMODULE_H
#define TESTMODULE_H

#include "keto/module/ModuleInterface.hpp"

namespace keto {
namespace test {


class TestModule : public keto::module::ModuleInterface {
public:
    TestModule();
    TestModule(const TestModule& orig) = delete;
    virtual ~TestModule();
    
    // meta methods
    virtual const std::string getName() const;
    virtual const std::string getDescription() const;
    virtual const std::string getVersion() const;
    
    
private:

};

}
}

#endif /* TESTMODULE_H */

