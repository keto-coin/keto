/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GenesisLoader.cpp
 * Author: ubuntu
 * 
 * Created on March 8, 2018, 10:02 AM
 */

#include <iostream>
#include <string>
#include "keto/block/GenesisLoader.hpp"
#include "keto/block/GenesisReader.hpp"

namespace keto {
namespace block {

GenesisLoader::GenesisLoader(const GenesisReader& reader) : reader(reader) {
}

GenesisLoader::GenesisLoader(const GenesisLoader& orig) : reader(orig.reader) {
}

GenesisLoader::~GenesisLoader() {
}

void GenesisLoader::load() {
    //std::cout << "Dump : "  << reader.getJsonData().dump() << std::endl;
    //std::cout << "Is object : "  << reader.getJsonData().is_object() << std::endl;
    //std::cout << "Is array : "  << reader.getJsonData().is_array() << std::endl;
    std::cout << "Value : "  << reader.getJsonData()["parent"] << std::endl;
    //std::cout << "Transaction : "  << reader.getJsonData()["transactions"].is_array() << std::endl;
    nlohmann::json transactions = reader.getJsonData()["transactions"].get<nlohmann::json>();
    for (auto& element : transactions) {
        //std::cout << element << '\n';
        //std::cout << "Account hash : "  << element["account_hash"] << std::endl;
        //std::cout << "Public Key : "  << element["public_key"] << std::endl;
        nlohmann::json changeset = element["change_set"].get<nlohmann::json>();
        for (nlohmann::json& element2 : changeset["rdf"]) {
            //std::cout << "Change set : "  << element2 << std::endl;
            for (nlohmann::json::iterator it = element2.begin(); it != element2.end(); ++it) {
                nlohmann::json predicate = it.value();
                std::cout << "key : " << it.key() << " : [" << predicate << "]" << std::endl;
                for (nlohmann::json::iterator predIter = predicate.begin(); predIter != predicate.end(); ++predIter) {
                    std::cout << "key : " << predIter.key() << std::endl;
                }
            }
        }
    }
    //for (nlohmann::json::iterator iter = reader.getJsonData()["transactions"].begin();
    //    iter != reader.getJsonData()["transactions"].end(); iter++ ) {
    //    nlohmann::json transaction = iter.value().get<nlohmann::json>();
    //    std::cout << "Object : "  << iter->value.is_object() << std::endl;
    //    if (iter->is_object()) {
    //        std::cout << "Account hash : "  << iter.value()["account_hash"] << std::endl;
    //    }
    //}
    
    //std::cout << "Transaction array : " << reader.getJsonData()["transactions"].is_array() << std::endl;
    //for (auto& element : reader.getJsonData()["transactions"]) {
    //    std::cout << "Elements in transaction [" << element << "]" << std::endl;
    //}
    //reader.getJsonData()["transactions"]
    //for (nlohmann::json::iterator iter = reader.getJsonData()["transactions"].begin();
    //        iter != reader.getJsonData()["transactions"].end(); iter++ ) {
    //    std::cout << "Is array : " << iter.value().is_array() << std::endl;
    //    std::cout << "Is boolean" << iter.value().is_boolean() << std::endl;
    //    std::cout << "Is number" << iter.value().is_number() << std::endl;
    //    std::cout << "Is number" << iter.value().is_object() << std::endl;
    //    std::cout << "Is number" << iter.value().is_string() << std::endl;
    //    std::cout << "account hash" << iter.value()["account_hash"].get<std::string>() << std::endl;
    //}
    
        
}




}
}
