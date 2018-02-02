/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NumberHelper.cpp
 * Author: ubuntu
 * 
 * Created on February 1, 2018, 4:25 PM
 */

#include "keto/asn1/NumberHelper.hpp"
#include "include/keto/asn1/NumberHelper.hpp"

namespace keto {
namespace asn1 {


NumberHelper::NumberHelper() : value(0) {
}

NumberHelper::NumberHelper(const long& number) : value(number) {
}

NumberHelper::NumberHelper(const Number_t& number) {
    asn_INTEGER2long(&number, &this->value);
}

NumberHelper::NumberHelper(const Number_t* number) {
    asn_INTEGER2long(number, &this->value);
}


NumberHelper::~NumberHelper() {
}

NumberHelper& NumberHelper::operator + (const int& rhs) {
    this->value = this->value + rhs;
    return (*this);
}

NumberHelper& NumberHelper::operator - (const int& rhs) {
    this->value = this->value - rhs;
    return (*this);
}


NumberHelper& NumberHelper::operator + (const long& rhs) {
    this->value = this->value + rhs;
    return (*this);
}


NumberHelper& NumberHelper::operator - (const long& rhs) {
    this->value = this->value - rhs;
    return (*this);
}

NumberHelper& NumberHelper::operator + (const NumberHelper& rhs) {
    this->value = this->value + rhs.value;
    return (*this);
}


NumberHelper& NumberHelper::operator - (const NumberHelper& rhs) {
    this->value = this->value - rhs.value;
    return (*this);
}

NumberHelper& NumberHelper::operator - (const Number_t* number) {
    long value;
    asn_INTEGER2long(number, &value);
    this->value -= value;
    return (*this);
}

NumberHelper& NumberHelper::operator + (const Number_t* number) {
    long value;
    asn_INTEGER2long(number, &value);
    this->value += value;
    return (*this);
}

NumberHelper& NumberHelper::operator - (const Number_t& number) {
    long value;
    asn_INTEGER2long(&number, &value);
    this->value -= value;
    return (*this);
}


NumberHelper& NumberHelper::operator + (const Number_t& number) {
    long value;
    asn_INTEGER2long(&number, &value);
    this->value += value;
    return (*this);
}


NumberHelper& NumberHelper::operator -= (const Number_t* number) {
    long value;
    asn_INTEGER2long(number, &value);
    this->value -= value;
    return (*this);
}

NumberHelper& NumberHelper::operator += (const Number_t* number) {
    long value;
    asn_INTEGER2long(number, &value);
    this->value += value;
    return (*this);
}

NumberHelper& NumberHelper::operator -= (const Number_t& number) {
    long value;
    asn_INTEGER2long(&number, &value);
    this->value -= value;
    return (*this);
}

NumberHelper& NumberHelper::operator += (const Number_t& number) {
    long value;
    asn_INTEGER2long(&number, &value);
    this->value += value;
    return (*this);
}


NumberHelper& NumberHelper::operator -= (const NumberHelper& number) {
    this->value -= number.value;
    return (*this);
}


NumberHelper& NumberHelper::operator += (const NumberHelper& number) {
    this->value += number.value;
    return (*this);
}


NumberHelper& NumberHelper::operator -= (const long& number) {
    this->value -= number;
    return (*this);
}


NumberHelper& NumberHelper::operator += (const long& number) {
    this->value += number;
    return (*this);
}


NumberHelper& NumberHelper::operator -= (const int& number) {
    this->value -= number;
    return (*this);
}


NumberHelper& NumberHelper::operator += (const int& number) {
    this->value += number;
    return (*this);
}


NumberHelper& NumberHelper::operator = (const long& number) {
    this->value = number;
    return (*this);
}


NumberHelper& NumberHelper::operator = (const Number_t& number) {
    long value;
    asn_INTEGER2long(&number, &value);
    this->value = value;
    return (*this);
}


NumberHelper& NumberHelper::operator = (const Number_t* number) {
    long value;
    asn_INTEGER2long(number, &value);
    this->value = value;
    return (*this);
}

NumberHelper& NumberHelper::operator = (const NumberHelper& number) {
    this->value = number.value;
    return (*this);
}

NumberHelper::operator Number_t() const {
    Number_t* value = (Number_t*)calloc(1,sizeof value);
    asn_long2INTEGER(value,this->value);
    Number_t result = *value;
    free(value);
    return result;
}


NumberHelper::operator long() const {
    return this->value;
}


}
}