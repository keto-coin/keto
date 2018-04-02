file(GLOB HEADERS "include/keto/block/*.hpp")

include_directories(${PROTOBUF_INCLUDE_DIR})

## SORT .cpp by most likely to change / break compile
add_library( 0020_keto_block_module
            SHARED

            BlockModuleManager.cpp
            BlockModule.cpp
            StorageManager.cpp
            BlockService.cpp
            EventRegistry.cpp
            Constants.cpp
            GenesisReader.cpp
            GenesisLoader.cpp
            BlockProducer.cpp
            TransactionProcessor.cpp

             ${HEADERS}
           )

target_link_libraries( 0020_keto_block_module
                            PRIVATE keto_block_db keto_chain_common keto_rocks_db
                            PRIVATE keto_server_common keto_asn1_common keto_asn1_protocol
                            PRIVATE keto_transaction_common keto_proto_environment ${PROTOBUF_LIBRARIES}
                            PRIVATE keto_crypto ${BOTAN_LIBRARIES} 
                            PRIVATE ${ROCKSDB_LIBRARY} ${ROCKSDB_EXTRA_LIBRARY} ${ROCKSDB_SNAPPY_LIBRARY}
                            PRIVATE ${OPENSSL_LIBRARIES} )
target_include_directories( 0020_keto_block_module
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_BINARY_DIR}/include"
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../../libs/common/include"
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../../libs/environment/include"
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../../libs/module_manager/include"
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../../libs/block_db/include"
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../../libs/chain_common/include"
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../../libs/event_service_api/include"
                            PUBLIC "${CMAKE_BINARY_DIR}/src/libs/common/include/"
                            PUBLIC "${CMAKE_BINARY_DIR}/src/libs/asn1/include/"
                            PUBLIC "${CMAKE_BINARY_DIR}/src/protocol/proto/"
                            PUBLIC "${PROTO_HDRS}"

                            ${Boost_INCLUDE_DIRS}
                            ${JSON_INCLUDE_DIR}
                            )

#if(MSVC)
#  set_source_files_properties( db_init.cpp db_block.cpp database.cpp block_log.cpp PROPERTIES COMPILE_FLAGS "/bigobj" )
#endif(MSVC)

INSTALL( TARGETS
   0020_keto_block_module

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION shared
   ARCHIVE DESTINATION shared
)
INSTALL( FILES ${HEADERS} DESTINATION "include/keto/block" )
