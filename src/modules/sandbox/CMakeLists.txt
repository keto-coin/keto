file(GLOB HEADERS "include/keto/rpc_server/*.hpp")

include_directories(${PROTOBUF_INCLUDE_DIR})

## SORT .cpp by most likely to change / break compile
add_library( 0020_keto_sandbox_module
            SHARED

            SandboxModuleManager.cpp
            SandboxModule.cpp
            EventRegistry.cpp
            SandboxService.cpp

             ${HEADERS}
           )

target_link_libraries( 0020_keto_sandbox_module 
                            PRIVATE keto_wavm_common keto_server_common
                            PRIVATE keto_transaction_common keto_proto_environment ${PROTOBUF_LIBRARIES}
                            PRIVATE keto_asn1_common keto_asn1_protocol
                            PRIVATE keto_crypto ${BOTAN_LIBRARIES} 
                            PRIVATE ${LIBRDF_LIBRARY} ${LIBRDF_RAPTOR_LIBRARY} 
                            PRIVATE ${LIBRDF_RASQAL_LIBRARY} 
                            PRIVATE ${LIBRDF_EXTRA_LIBRARY} ${LIBRDF_XML_EXTRA_LIBRARY} 
                            PRIVATE ${LIBRDF_PCRE_EXTRA_LIBRARY} ${LIBRDF_LTDL_EXTRA_LIBRARY}
                            PRIVATE ${LIBRDF_GMP_EXTRA_LIBRARY}
                            PRIVATE ${OPENSSL_LIBRARIES} )
target_include_directories( 0020_keto_sandbox_module
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_BINARY_DIR}/include"
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../../libs/common/include"
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../../libs/environment/include"
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../../libs/module_manager/include"
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../../libs/event_service_api/include"
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../../libs/server_common/include"
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../../libs/wavm_common/include"
                            PUBLIC "${CMAKE_BINARY_DIR}/src/libs/common/include/"

                            ${Boost_INCLUDE_DIRS}
                            )

#if(MSVC)
#  set_source_files_properties( db_init.cpp db_block.cpp database.cpp block_log.cpp PROPERTIES COMPILE_FLAGS "/bigobj" )
#endif(MSVC)

INSTALL( TARGETS
   0020_keto_sandbox_module

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION shared
   ARCHIVE DESTINATION shared
)
INSTALL( FILES ${HEADERS} DESTINATION "include/keto/rpc_server" )
