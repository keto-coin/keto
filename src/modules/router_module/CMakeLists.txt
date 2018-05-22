file(GLOB HEADERS "include/keto/router/*.hpp")

include_directories(${PROTOBUF_INCLUDE_DIR})

## SORT .cpp by most likely to change / break compile
add_library( 0015_keto_router_module
            SHARED

            RouterModuleManager.cpp
            RouterModule.cpp
            RouterService.cpp
            EventRegistry.cpp
            StorageManager.cpp
            RouterRegistry.cpp

             ${HEADERS}
           )

target_link_libraries( 0015_keto_router_module 
                            PRIVATE keto_router_db keto_rocks_db
                            PRIVATE keto_server_common
                            PRIVATE keto_transaction_common keto_proto_environment ${PROTOBUF_LIBRARIES}
                            PRIVATE keto_asn1_common keto_asn1_protocol
                            PRIVATE keto_crypto ${BOTAN_LIBRARIES} 
                            PRIVATE ${ROCKSDB_LIBRARY} ${ROCKSDB_EXTRA_LIBRARY}
                            PRIVATE ${OPENSSL_LIBRARIES} )
target_include_directories( 0015_keto_router_module
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_BINARY_DIR}/include"
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../../libs/common/include"
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../../libs/environment/include"
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../../libs/module_manager/include"
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../../libs/event_service_api/include"
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../../libs/transaction_common/include"
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../../libs/server_common/include"
                            PUBLIC "${CMAKE_BINARY_DIR}/src/libs/common/include/"
                            PUBLIC "${CMAKE_BINARY_DIR}/src/protocol/proto/"
                            PUBLIC "${PROTO_HDRS}"
                            
                            ${Boost_INCLUDE_DIRS}
                            )

#if(MSVC)
#  set_source_files_properties( db_init.cpp db_block.cpp database.cpp block_log.cpp PROPERTIES COMPILE_FLAGS "/bigobj" )
#endif(MSVC)

INSTALL( TARGETS
   0015_keto_router_module

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION shared
   ARCHIVE DESTINATION shared
)
INSTALL( FILES ${HEADERS} DESTINATION "include/keto/router" )
