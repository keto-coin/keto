/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GenesisReader.hpp
 * Author: ubuntu
 *
 * Created on March 8, 2018, 9:36 AM
 */

#ifndef GENESISREADER_HPP
#define GENESISREADER_HPP

#include <string>
#include <nlohmann/json.hpp>
#include <boost/filesystem/path.hpp>


namespace keto {
namespace block {

class GenesisReader {
public:
    GenesisReader(const boost::filesystem::path& path);
    GenesisReader(const GenesisReader& orig) = default;
    virtual ~GenesisReader();
    
    nlohmann::json getJsonData();
private:
    nlohmann::json jsonData;
};


}
}


#endif /* GENESISREADER_HPP */

