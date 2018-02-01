/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TimeHelper.cpp
 * Author: brett chaldecott
 * 
 * Created on January 31, 2018, 8:12 AM
 */

#include "keto/asn1/TimeHelper.hpp"

namespace keto {
namespace asn1 {

TimeHelper::TimeHelper() {
    this->time_point = std::chrono::system_clock::now();
}

TimeHelper::~TimeHelper() {
}

TimeHelper& TimeHelper::operator =(const UTCTime_t& time) {
    std::tm timeinfo;
    asn_UT2time(&time, &timeinfo, 1);
    this->time_point = 
            std::chrono::system_clock::from_time_t (
            std::mktime(&timeinfo));
    return (*this);
}

TimeHelper& TimeHelper::operator =(const UTCTime_t* time) {
    std::tm timeinfo;
    asn_UT2time(time, &timeinfo, 1);
    this->time_point = 
            std::chrono::system_clock::from_time_t (
            std::mktime(&timeinfo));
    return (*this);
}

TimeHelper::operator UTCTime_t() const {
    // standard time
    std::time_t timeT = 
            std::chrono::system_clock::to_time_t(this->time_point);
    
    // convert to uct time
    UTCTime_t* uctTime_t = (UTCTime_t*)calloc(1, sizeof *uctTime_t);
    asn_time2UT(uctTime_t, localtime(&timeT), 1);
    UTCTime_t result = *uctTime_t;
    free(uctTime_t);
    return result;
}

TimeHelper& TimeHelper::operator =(const std::time_t& time) {
    this->time_point = std::chrono::system_clock::from_time_t (time);
    return *this;
}
    
TimeHelper::operator std::time_t() const {
    return std::chrono::system_clock::to_time_t(time_point);
}

TimeHelper& TimeHelper::operator =(const std::chrono::system_clock::time_point& time) {
    this->time_point = time;
    return *this;
}

TimeHelper::operator std::chrono::system_clock::time_point() const {
    return time_point;
}


}
}