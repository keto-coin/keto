/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MetaInfo.hpp
 * Author: ubuntu
 *
 * Created on January 13, 2018, 3:03 AM
 */

#ifndef METAINFO_HPP
#define METAINFO_HPP

namespace keto {
namespace common {

/**
 * This class contains the meta information for the 
 */
class MetaInfo {

public:
    MetaInfo() = delete;
    MetaInfo(const MetaInfo& orig) = delete;
    virtual ~MetaInfo() = delete;
    
    static constexpr const char* COPY_RIGHT;
    static constexpr const char* VERSION;
    static constexpr const char* NETWORK_VERSION;
    static constexpr const char* BLOCKCHAIN_NAME;
    
private:

};


}
}

#endif /* METAINFO_HPP */

