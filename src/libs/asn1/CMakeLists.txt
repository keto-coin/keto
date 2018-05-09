file(GLOB HEADERS "include/keto/asn1/*.hpp")

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

## SORT .cpp by most likely to change / break compile
add_library( keto_asn1_common
            
            TimeHelper.cpp
            NumberHelper.cpp
            HashHelper.cpp
            KeyHelper.cpp
            AnyHelper.cpp
            TestEntityHelper.cpp
            PrivateKeyHelper.cpp
            SignatureHelper.cpp
            BerEncodingHelper.cpp
            RDFObjectHelper.cpp
            RDFPredicateHelper.cpp
            RDFSubjectHelper.cpp
            RDFModelHelper.cpp
            ChangeSetHelper.cpp
            ContractHelper.cpp

             ${HEADERS}
           )

target_link_libraries( keto_asn1_common )
target_include_directories( keto_asn1_common
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_BINARY_DIR}/include"
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../common/include"
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../crypto/include/"
                            PUBLIC "${CMAKE_BINARY_DIR}/src/protocol/asn1/" 
                            PUBLIC "${CMAKE_BINARY_DIR}/src/libs/common/include/" 
                            ${Boost_INCLUDE_DIRS}
                            ${BOTAN_INCLUDE_DIR}
                            )

#if(MSVC)
#  set_source_files_properties( db_init.cpp db_block.cpp database.cpp block_log.cpp PROPERTIES COMPILE_FLAGS "/bigobj" )
#endif(MSVC)

INSTALL( TARGETS
   keto_asn1_common

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
INSTALL( FILES ${HEADERS} DESTINATION "include/keto/asn1" )
