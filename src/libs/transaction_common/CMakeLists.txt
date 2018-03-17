file(GLOB HEADERS "include/keto/transaction_common/*.hpp")

## SORT .cpp by most likely to change / break compile
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
add_library( keto_transaction_common
            
            TransactionTraceBuilder.cpp
            ChangeSetBuilder.cpp
            SignedChangeSetBuilder.cpp
            TransactionMessageHelper.cpp 
            
             ${HEADERS}
           )

target_link_libraries( keto_transaction_common )
target_include_directories( keto_transaction_common
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_BINARY_DIR}/include"
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../common/include"
                            PUBLIC "${CMAKE_BINARY_DIR}/src/protocol/asn1/" 
                            PUBLIC "${CMAKE_BINARY_DIR}/src/libs/common/include/" 
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../asn1/include"
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../crypto/include/"
                            ${Boost_INCLUDE_DIRS}
                            ${BOTAN_INCLUDE_DIR}
                            )

#if(MSVC)
#  set_source_files_properties( db_init.cpp db_block.cpp database.cpp block_log.cpp PROPERTIES COMPILE_FLAGS "/bigobj" )
#endif(MSVC)

INSTALL( TARGETS
   keto_transaction_common

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
INSTALL( FILES ${HEADERS} DESTINATION "include/keto/transaction_common" )
