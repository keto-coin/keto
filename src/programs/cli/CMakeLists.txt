add_executable( keto_cli main.cpp )
if( UNIX AND NOT APPLE )
  set(rt_library rt )
endif()

find_package( Gperftools QUIET )
if( GPERFTOOLS_FOUND )
    message( STATUS "Found gperftools; compiling keto_cli with TCMalloc")
    list( APPEND PLATFORM_SPECIFIC_LIBS tcmalloc )
endif()

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/../../../.git)
  find_package(Git)
  if(GIT_FOUND)
    execute_process(
      COMMAND ${GIT_EXECUTABLE} rev-parse --short=8 HEAD
      WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../.."
      OUTPUT_VARIABLE "keto_cli_BUILD_VERSION"
      ERROR_QUIET
      OUTPUT_STRIP_TRAILING_WHITESPACE)
    message(STATUS "Git commit revision: ${keto_cli_BUILD_VERSION}")
  else()
    set(keto_cli_BUILD_VERSION 0)
  endif()
endif()

#configure_file(config.hpp.in config.hpp ESCAPE_QUOTES)

include_directories(${PROTOBUF_INCLUDE_DIR})

target_include_directories(keto_cli
        PUBLIC ${CMAKE_CURRENT_BINARY_DIR}
        PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include"
        PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../../libs/ssl/include"
        PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../../libs/http_client_session/include"
        PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../../libs/common/include"
        PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../../libs/chain_common/include"
        PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../../libs/evironment/include"
        PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../../libs/account_utils/include"
        PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include"
        PUBLIC "${CMAKE_BINARY_DIR}/src/protocol/proto/"
        ${BOTAN_INCLUDE_DIR}
        ${JSON_INCLUDE_DIR})

target_link_libraries( keto_cli 
        PRIVATE keto_http_client_session keto_crypto  keto_account_utils
        PRIVATE keto_transaction_common keto_server_common keto_environment 
        PRIVATE keto_common keto_chain_common
        PRIVATE keto_asn1_common keto_asn1_protocol
        PRIVATE keto_proto_environment ${PROTOBUF_LIBRARIES} 
        PRIVATE ${BOTAN_LIBRARIES} ${Boost_LIBRARIES} 
        PRIVATE ${OPENSSL_LIBRARIES}  ${pthread_library}
        PRIVATE ${CMAKE_DL_LIBS} ${PLATFORM_SPECIFIC_LIBS} 
        )

install( TARGETS
   keto_cli

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
