/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TimeHelper.hpp
 * Author: ubuntu
 *
 * Created on January 31, 2018, 8:12 AM
 */

#ifndef TIMEHELPER_HPP
#define TIMEHELPER_HPP

#include "UTCTime.h"
#include <chrono>

namespace keto {
namespace asn1 {

class TimeHelper {
public:
    TimeHelper();
    TimeHelper(const TimeHelper& orig) = default;
    virtual ~TimeHelper();
    
    
    TimeHelper& operator =(const UTCTime_t& time);
    TimeHelper& operator =(const UTCTime_t* time);
    operator UTCTime_t() const;
    TimeHelper& operator =(const std::time_t& time);
    operator std::time_t() const;
    TimeHelper& operator =(const std::chrono::system_clock::time_point& time);
    operator std::chrono::system_clock::time_point() const;
    
private:
    std::chrono::system_clock::time_point time_point;
};

}
}

#endif /* TIMEHELPER_HPP */

