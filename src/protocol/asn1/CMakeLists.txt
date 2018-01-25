find_package(Asn1 REQUIRED)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

asn1_generate_cpp(ASN1_SRCS ASN1_HDRS BlockChain.asn1)

add_library(keto_asn1_protocol ${ASN1_SRCS} )

SET_TARGET_PROPERTIES(keto_asn1_protocol PROPERTIES LINKER_LANGUAGE C)

target_include_directories( keto_asn1_protocol
                PUBLIC "${ASN1_HDRS}")

target_link_libraries( keto_asn1_protocol )