/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SliceHelper.cpp
 * Author: ubuntu
 * 
 * Created on February 28, 2018, 1:28 PM
 */

#include <rocksdb/slice.h>
#include <vector>
#include <sstream>

#include "keto/rocks_db/SliceHelper.hpp"

namespace keto {
namespace rocks_db {


SliceHelper::SliceHelper() {
}

SliceHelper::SliceHelper(const std::string& sliceBytes) {
    for(const char entry : sliceBytes) {
        this->sliceBytes.push_back((uint8_t)entry);
    }
}


SliceHelper::SliceHelper(const std::vector<uint8_t>& sliceBytes) : 
sliceBytes(sliceBytes) {    
}


SliceHelper::SliceHelper(const rocksdb::Slice& slice) {
    if (!slice.empty()) {
        for (int index = 0; index < slice.size_; index++) {
            sliceBytes.push_back(slice.data_[index]);
        }
    }
}


SliceHelper::~SliceHelper() {
}

SliceHelper& SliceHelper::operator = (const std::string& sliceBytes) {
    for(const char entry : sliceBytes) {
        this->sliceBytes.push_back((uint8_t)entry);
    }
    return (*this);
}
    

SliceHelper& SliceHelper::operator = (const std::vector<uint8_t>& sliceBytes) {
    this->sliceBytes = sliceBytes;
    return (*this);
}

SliceHelper& SliceHelper::operator = (const rocksdb::Slice& slice) {
    if (!slice.empty()) {
        for (int index = 0; index < slice.size_; index++) {
            sliceBytes.push_back(slice.data_[index]);
        }
    }
    return (*this);
}

SliceHelper::operator rocksdb::Slice () {
    rocksdb::Slice slice((const char*)this->sliceBytes.data(),this->sliceBytes.size());
    return slice;
}

SliceHelper::operator std::vector<uint8_t> () {
    return this->sliceBytes;
}

SliceHelper::operator std::string () {
    std::stringstream ss;
    for (uint8_t entry : this->sliceBytes) {
        ss << (char)entry;
    }
    return ss.str();
}
    

}
}