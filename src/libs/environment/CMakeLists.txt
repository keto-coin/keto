file(GLOB HEADERS "include/keto/environment/*.hpp")

## SORT .cpp by most likely to change / break compile
add_library( keto_environment
            
            Env.cpp 
            EnvironmentManager.cpp

             ${HEADERS}
           )

target_link_libraries( keto_environment )
target_include_directories( keto_environment
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_BINARY_DIR}/include"
                            )

#if(MSVC)
#  set_source_files_properties( db_init.cpp db_block.cpp database.cpp block_log.cpp PROPERTIES COMPILE_FLAGS "/bigobj" )
#endif(MSVC)

INSTALL( TARGETS
   keto_environment

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
INSTALL( FILES ${HEADERS} DESTINATION "include/keto/environment" )
