/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HttpSession.cpp
 * Author: ubuntu
 * 
 * Created on February 13, 2018, 7:55 AM
 */

#include <sstream> 

#include <boost/beast/http/message.hpp>
#include <botan/pkcs8.h>
#include <botan/hex.h>

// protobuf includes
#include "HandShake.pb.h"

#include "keto/common/HttpEndPoints.hpp"
#include "keto/session/HttpSession.hpp"
#include "keto/common/Constants.hpp"
#include "keto/session/HttpSession.hpp"
#include "keto/crypto/HashGenerator.hpp"
#include "keto/crypto/SignatureGenerator.hpp"
#include "keto/session/HttpSession.hpp"
#include "keto/session/Exception.hpp"


namespace keto {
namespace session {


HttpSession::HttpSession(
        boost::asio::io_context& ioc, boost::asio::ssl::context& ctx,
        const std::string& privateKey, const std::string& publicKey) :
    ioc(ioc), ctx(ctx), keyLoader(privateKey,publicKey) {
    
    
    
}

HttpSession::~HttpSession() {
}

HttpSession& HttpSession::setHost(const std::string& host) {
    this->host = host;
    return (*this);
}


std::string HttpSession::getHost() {
    return this->host;
}


HttpSession& HttpSession::setPort(const std::string& port) {
    this->port = port;
    return (*this);
}


std::string HttpSession::getPort() {
    return this->port;
}


HttpSession& HttpSession::handShake() {
    
    // setup the crypto
    keto::crypto::SecureVector publicKeyHashVector = keto::crypto::HashGenerator().generateHash(
            Botan::X509::BER_encode(*this->keyLoader.getPublicKey()));
    std::vector<uint8_t> signatureHashVector =
            keto::crypto::SignatureGenerator(this->keyLoader).sign(publicKeyHashVector);
    
    keto::proto::ClientHello clientHello;
    clientHello.set_version(keto::common::MetaInfo::PROTOCOL_VERSION);
    clientHello.set_client_hash(publicKeyHashVector.data(),publicKeyHashVector.size());
    clientHello.set_signature(signatureHashVector.data(),signatureHashVector.size());
    
    std::string buffer;
    clientHello.SerializeToString(&buffer);
    boost::beast::http::response<boost::beast::http::string_body> response = 
        this->makeRequest(this->createProtobufRequest(buffer));
    
    keto::proto::ClientResponse clientResponse;
    clientResponse.ParseFromString(response.body());
    if (clientResponse.response() != keto::proto::HelloResponse::WELCOME) {
        BOOST_THROW_EXCEPTION(keto::session::ClientAuthorizationFailureException());
    }
    
    std::cout << "Finished : " << clientResponse.response() << "was expecting " << 
            keto::proto::HelloResponse::WELCOME << std::endl;
    return (*this);
}

std::string HttpSession::makeRequest(const std::string& request) {
    
    return "After making request";
}

boost::beast::http::request<boost::beast::http::string_body>
HttpSession::createProtobufRequest(const std::string& buffer) {
    boost::beast::http::request<boost::beast::http::string_body> req{boost::beast::http::verb::post, 
            keto::common::HttpEndPoints::HAND_SHAKE, 
            keto::common::Constants::HTTP_VERSION};
    req.insert(keto::common::Constants::CONTENT_TYPE_HEADING,
            keto::common::Constants::PROTOBUF_CONTENT_TYPE);
    req.body() = buffer;
    req.content_length(buffer.size());
    return req;
}

boost::beast::http::response<boost::beast::http::string_body> 
HttpSession::makeRequest(boost::beast::http::request<boost::beast::http::string_body> request) {
    
    boost::asio::ip::tcp::resolver resolver{this->ioc};
    boost::asio::ssl::stream<boost::asio::ip::tcp::socket> stream{this->ioc, this->ctx};
    
    // Look up the domain name
    auto const results = resolver.resolve(this->host, this->port);
    
    // Make the connection on the IP address we get from a lookup
    boost::asio::connect(stream.next_layer(), results.begin(), results.end());

    // Perform the SSL handshake
    stream.handshake(boost::asio::ssl::stream_base::client);

    // Set up an HTTP GET request message
    request.set(boost::beast::http::field::host, this->host);
    request.set(boost::beast::http::field::user_agent, BOOST_BEAST_VERSION_STRING);

    // Send the HTTP request to the remote host
    boost::beast::http::write(stream, request);

    // This buffer is used for reading and must be persisted
    boost::beast::flat_buffer buffer;

    // Declare a container to hold the response
    boost::beast::http::response<boost::beast::http::string_body> res;

    // Receive the HTTP response
    boost::beast::http::read(stream, buffer, res);
    
    // stream shutdown
    boost::system::error_code ec;
    stream.shutdown(ec);

    // check if the ec error is eof and reset
    //if(ec == boost::asio::error::eof)
    //{
    //    ec.assign(0, ec.category());
    //}
    // check if there is an error
    //if(ec) {
    //    BOOST_THROW_EXCEPTION(keto::session::ClientFailedToCloseSocketException(
    //            ec.message()));
    //}
    
    if (res.result() != boost::beast::http::status::ok) {
        std::stringstream ss;
        ss << "Http session call failed : " << std::endl << res;
        BOOST_THROW_EXCEPTION(keto::session::ClientHandShakeFailureException(
                ss.str()));
    }
    
    return res;
}

}
}