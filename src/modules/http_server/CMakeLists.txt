file(GLOB HEADERS "include/keto/http/*.hpp")

include_directories(${PROTOBUF_INCLUDE_DIR})

## SORT .cpp by most likely to change / break compile
add_library( 0050_keto_httpd_module
            SHARED

            HttpdModuleManager.cpp
            HttpdModule.cpp
            HttpdServer.cpp

             ${HEADERS}
           )

target_link_libraries( 0050_keto_httpd_module 
                            PRIVATE keto_http_server_session keto_server_common
                            PRIVATE keto_proto_environment ${PROTOBUF_LIBRARIES}
                            PRIVATE keto_crypto ${BOTAN_LIBRARIES} 
                            PRIVATE ${OPENSSL_LIBRARIES}
 )
target_include_directories( 0050_keto_httpd_module
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_BINARY_DIR}/include"
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../../libs/common/include"
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../../libs/environment/include"
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../../libs/module_manager/include"
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../../libs/event_service_api/include"
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../../libs/transaction_manager_api/include"
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../../libs/http_server_session/include"
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../../libs/ssl/include"
                            PUBLIC "${CMAKE_BINARY_DIR}/src/libs/common/include/"
                            PUBLIC "${CMAKE_BINARY_DIR}/src/protocol/proto/"
                            PUBLIC "${PROTO_HDRS}"

                            ${Boost_INCLUDE_DIRS}
                            )

#if(MSVC)
#  set_source_files_properties( db_init.cpp db_block.cpp database.cpp block_log.cpp PROPERTIES COMPILE_FLAGS "/bigobj" )
#endif(MSVC)

INSTALL( TARGETS
   0050_keto_httpd_module

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION shared
   ARCHIVE DESTINATION shared
)
INSTALL( FILES ${HEADERS} DESTINATION "include/keto/http" )
