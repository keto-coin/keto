/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SliceHelper.hpp
 * Author: ubuntu
 *
 * Created on February 28, 2018, 1:27 PM
 */

#ifndef SLICEHELPER_HPP
#define SLICEHELPER_HPP

#include <string>
#include <memory>

#include "rocksdb/slice.h"

namespace keto {
namespace rocks_db {

class SliceHelper {
public:
    SliceHelper();
    SliceHelper(const std::vector<uint8_t>& sliceBytes);
    SliceHelper(const rocksdb::Slice& slice);
    
    SliceHelper(const SliceHelper& orig) = default;
    virtual ~SliceHelper();
    
    SliceHelper& operator = (const std::vector<uint8_t>& sliceBytes);
    SliceHelper& operator = (const rocksdb::Slice& slice);
    
    operator rocksdb::Slice ();
    operator std::vector<uint8_t> ();
    
private:
    std::vector<uint8_t> sliceBytes;
};


}
}

#endif /* SLICEHELPER_HPP */

