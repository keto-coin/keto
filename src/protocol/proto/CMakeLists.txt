find_package(Protobuf REQUIRED)

include_directories(${PROTOBUF_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS BlockChain.proto)

add_library(keto_protocol ${PROTO_SRCS} )

target_include_directories( keto_environment
                PUBLIC "${PROTO_HDRS}")

target_link_libraries( keto_environment )