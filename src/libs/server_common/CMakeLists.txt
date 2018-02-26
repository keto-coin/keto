file(GLOB HEADERS "include/keto/server_common/*.hpp")

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

## SORT .cpp by most likely to change / break compile
add_library( keto_server_common
            
	      Constants.cpp
              ServerInfo.cpp
              VectorUtils.cpp
              Events.cpp
              EventServiceHelpers.cpp
              TransactionHelper.cpp

             ${HEADERS}
           )

target_link_libraries( keto_server_common )
target_include_directories( keto_server_common
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_BINARY_DIR}/include"
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../common/include"
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../environment/include"
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../event_service_api/include"
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../transaction_manager_api/include"
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../module_manager/include"
                            ${Boost_INCLUDE_DIRS}
                            ${BOTAN_INCLUDE_DIR}
                            )

#if(MSVC)
#  set_source_files_properties( db_init.cpp db_block.cpp database.cpp block_log.cpp PROPERTIES COMPILE_FLAGS "/bigobj" )
#endif(MSVC)

INSTALL( TARGETS
   keto_server_common

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
INSTALL( FILES ${HEADERS} DESTINATION "include/keto/server_common" )
