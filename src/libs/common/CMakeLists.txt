file(GLOB HEADERS "include/keto/common/*.hpp")

# parse the configuration file
configure_file(MetaInfo.cpp.in MetaInfo.cpp)

## SORT .cpp by most likely to change / break compile
add_library( keto_common
            
			Exception.cpp
                        MetaInfo.cpp

             ${HEADERS}
           )

target_link_libraries( keto_common )
target_include_directories( keto_common
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_BINARY_DIR}/include"
                            ${Boost_INCLUDE_DIRS}
                            )

#if(MSVC)
#  set_source_files_properties( db_init.cpp db_block.cpp database.cpp block_log.cpp PROPERTIES COMPILE_FLAGS "/bigobj" )
#endif(MSVC)

INSTALL( TARGETS
   keto_common

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
INSTALL( FILES ${HEADERS} DESTINATION "include/keto/common" )
