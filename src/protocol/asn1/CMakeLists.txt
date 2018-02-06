find_package(Asn1 REQUIRED)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

asn1_generate_cpp(ASN1_SRCS ASN1_HDRS Basic.asn1 PrivateKey.asn1 PublicKey.asn1 Test.asn1 Security.asn1 Account.asn1 Contract.asn1 Action.asn1 Transaction.asn1 BlockChain.asn1 )

add_library(keto_asn1_protocol ${ASN1_SRCS} )

# set the necessary compile commands
target_compile_options(keto_asn1_protocol PUBLIC "-DASN_PDU_COLLECTION")

target_include_directories( keto_asn1_protocol
                PUBLIC "${ASN1_HDRS}")

target_link_libraries( keto_asn1_protocol )