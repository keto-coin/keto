file(GLOB HEADERS "include/keto/wavm_common/*.hpp")

include_directories(${PROTOBUF_INCLUDE_DIR})

## SORT .cpp by most likely to change / break compile
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if(MSVC)
    add_definitions("-DDLL_EXPORT=__declspec(dllexport)")
    add_definitions("-DDLL_IMPORT=__declspec(dllimport)")
else()
    add_definitions(-DDLL_EXPORT=)
    add_definitions(-DDLL_IMPORT=)
endif()

add_library( keto_wavm_common
            
            WavmEngineManager.cpp
            WavmEngineWrapper.cpp
            
             ${HEADERS}
           )

target_link_libraries( keto_wavm_common 
                    ${LIBWAVM_RUNTIME_LIBRARY}
                    ${LIBWAVM_LIBRARY}
                    ${LIBWAVM_WAST_LIBRARY}
                    ${LIBWAVM_LOGGING_LIBRARY}
                    ${LIBWAVM_EMSCRIPTEN_LIBRARY}
                    ${LIBWAVM_IR_LIBRARY}
                    ${LIBWAVM_EXTRA_LIBRARY}
                    ${LIBWAVM_PLATFORM_LIBRARY}
                    ${LIBWAVM_LLVM_LIBS})
target_include_directories( keto_wavm_common
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_BINARY_DIR}/include"
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../common/include"
                            PUBLIC "${CMAKE_BINARY_DIR}/src/protocol/asn1/" 
                            PUBLIC "${CMAKE_BINARY_DIR}/src/protocol/proto/" 
                            PUBLIC "${CMAKE_BINARY_DIR}/src/libs/common/include/" 
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../asn1/include"
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../crypto/include/"
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../server_common/include/"
                            PUBLIC "${PROTO_HDRS}"
                            ${Boost_INCLUDE_DIRS}
                            ${BOTAN_INCLUDE_DIR}
                            ${LIBWAVM_INCLUDE_DIR}
                            ${LIBWAVM_LLVM_INCLUDE_DIRS}
                            )

#if(MSVC)
#  set_source_files_properties( db_init.cpp db_block.cpp database.cpp block_log.cpp PROPERTIES COMPILE_FLAGS "/bigobj" )
#endif(MSVC)

INSTALL( TARGETS
   keto_wavm_common

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
INSTALL( FILES ${HEADERS} DESTINATION "include/keto/wavm_common" )
