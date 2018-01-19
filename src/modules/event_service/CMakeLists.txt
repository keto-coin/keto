file(GLOB HEADERS "include/keto/event/*.hpp")

## SORT .cpp by most likely to change / break compile
add_library( 0002_keto_event_service_module
            SHARED

            EventServiceModuleManager.cpp
            EventServiceModule.cpp

             ${HEADERS}
           )

target_link_libraries( 0002_keto_event_service_module )
target_include_directories( 0002_keto_event_service_module
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_BINARY_DIR}/include"
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../../libs/common/include"
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../../libs/environment/include"
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../../libs/module_manager/include"
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../../libs/event_service_api/include"

                            ${Boost_INCLUDE_DIRS}
                            )

#if(MSVC)
#  set_source_files_properties( db_init.cpp db_block.cpp database.cpp block_log.cpp PROPERTIES COMPILE_FLAGS "/bigobj" )
#endif(MSVC)

INSTALL( TARGETS
   0002_keto_event_service_module

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION shared
   ARCHIVE DESTINATION shared
)
INSTALL( FILES ${HEADERS} DESTINATION "include/keto/event" )
