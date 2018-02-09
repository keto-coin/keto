find_package(Protobuf REQUIRED)

include_directories(${PROTOBUF_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS BlockChain.proto HandShake.proto Protocol.proto Route.proto Balancer.proto)

add_library(keto_proto_environment ${PROTO_SRCS} )

target_include_directories( keto_proto_environment
                PUBLIC "${PROTO_HDRS}")

target_link_libraries( keto_proto_environment )