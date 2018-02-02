/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NumberHelper.hpp
 * Author: ubuntu
 *
 * Created on February 1, 2018, 4:25 PM
 */

#ifndef NUMBERHELPER_HPP
#define NUMBERHELPER_HPP

#include "Number.h"

namespace keto {
namespace asn1 {

class NumberHelper {
public:
    NumberHelper();
    NumberHelper(const long& number);
    NumberHelper(const Number_t& number);
    NumberHelper(const Number_t* number);
    NumberHelper(const NumberHelper& orig) = default;
    virtual ~NumberHelper();
    
    NumberHelper& operator + (const int& rhs);
    NumberHelper& operator - (const int& rhs);
    NumberHelper& operator + (const long& rhs);
    NumberHelper& operator - (const long& rhs);
    NumberHelper& operator + (const NumberHelper& rhs);
    NumberHelper& operator - (const NumberHelper& rhs);
    NumberHelper& operator - (const Number_t* number);
    NumberHelper& operator + (const Number_t* number);
    NumberHelper& operator - (const Number_t& number);
    NumberHelper& operator + (const Number_t& number);
    NumberHelper& operator -= (const Number_t* number);
    NumberHelper& operator += (const Number_t* number);
    NumberHelper& operator -= (const Number_t& number);
    NumberHelper& operator += (const Number_t& number);
    NumberHelper& operator -= (const int& number);
    NumberHelper& operator += (const int& number);
    NumberHelper& operator -= (const long& number);
    NumberHelper& operator += (const long& number);
    NumberHelper& operator -= (const NumberHelper& number);
    NumberHelper& operator += (const NumberHelper& number);
    NumberHelper& operator = (const long& number);
    NumberHelper& operator = (const Number_t& number);
    NumberHelper& operator = (const Number_t* number);
    NumberHelper& operator = (const NumberHelper& number);
    
    operator Number_t() const;
    operator long() const;
    
private:
    long value;
};


}
}

#endif /* NUMBERHELPER_HPP */

