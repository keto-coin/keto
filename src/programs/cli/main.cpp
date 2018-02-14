
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/error.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <cstdlib>
#include <iostream>
#include <string>
#include <boost/exception/exception.hpp>
#include <boost/exception/diagnostic_information.hpp>
#include <boost/exception_ptr.hpp> 

#include "keto/common/MetaInfo.hpp"
#include "keto/common/Log.hpp"
#include "keto/common/Exception.hpp"
#include "keto/environment/EnvironmentManager.hpp"
#include "keto/environment/Constants.hpp"
#include "keto/ssl/RootCertificate.hpp"
#include "keto/cli/Constants.hpp"
#include "keto/session/HttpSession.hpp"

namespace ketoEnv = keto::environment;
namespace ketoCommon = keto::common;
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
namespace ssl = boost::asio::ssl;       // from <boost/asio/ssl.hpp>
namespace http = boost::beast::http;    // from <boost/beast/http.hpp>

boost::program_options::options_description generateOptionDescriptions() {
    boost::program_options::options_description optionDescripion;
    
    optionDescripion.add_options()
            ("help,h", "Print this help message and exit.")
            ("version,v", "Print version information.");
    
    return optionDescripion;
}

/**
 * The CLI main file
 * 
 * @param argc
 * @param argv
 * @return 
 */
int main(int argc, char** argv)
{
    try {
        boost::program_options::options_description optionDescription =
                generateOptionDescriptions();
        
        std::shared_ptr<ketoEnv::EnvironmentManager> manager = 
                keto::environment::EnvironmentManager::init(
                keto::environment::Constants::KETO_CLI_CONFIG_FILE,
                optionDescription,argc,argv);
        
        std::shared_ptr<ketoEnv::Config> config = manager->getConfig();
        
        if (config->getVariablesMap().count(ketoEnv::Constants::KETO_VERSION)) {
            std::cout << ketoCommon::MetaInfo::VERSION << std::endl;
            return 0;
        }
        
        if (config->getVariablesMap().count(ketoEnv::Constants::KETO_HELP)) {
            std::cout <<  optionDescription << std::endl;
            return 0;
        }
        
        // retrieve the host information from the configuration file
        if (!config->getVariablesMap().count(keto::cli::Constants::KETOD_SERVER)) {
            std::cerr << "Please configure the ketod server host information [" << 
                    keto::cli::Constants::KETOD_SERVER << "]" << std::endl;
            return -1;
        }
        std::string host = config->getVariablesMap()[keto::cli::Constants::KETOD_SERVER].as<std::string>();
        
        // retrieve the host information from the configuration file
        if (!config->getVariablesMap().count(keto::cli::Constants::KETOD_PORT)) {
            std::cerr << "Please configure the ketod server port information [" << 
                    keto::cli::Constants::KETOD_PORT << "]" << std::endl;
            return -1;
        }
        std::string port = config->getVariablesMap()[keto::cli::Constants::KETOD_PORT].as<std::string>();
        
        // retrieve the host information from the configuration file
        if (!config->getVariablesMap().count(keto::cli::Constants::PRIVATE_KEY)) {
            std::cerr << "Please configure the private key [" << 
                    keto::cli::Constants::PRIVATE_KEY << "]" << std::endl;
            return -1;
        }
        std::string privateKey = config->getVariablesMap()[keto::cli::Constants::PRIVATE_KEY].as<std::string>();
        
        // retrieve the host information from the configuration file
        if (!config->getVariablesMap().count(keto::cli::Constants::PUBLIC_KEY)) {
            std::cerr << "Please configure the public key [" << 
                    keto::cli::Constants::PUBLIC_KEY << "]" << std::endl;
            return -1;
        }
        std::string publicKey = config->getVariablesMap()[keto::cli::Constants::PUBLIC_KEY].as<std::string>();
        
        
        // Check command line arguments.
        /*if(argc != 4 && argc != 5)
        {
            std::cerr <<
                "Usage: http-client-sync-ssl <host> <port> <target> [<HTTP version: 1.0 or 1.1(default)>]\n" <<
                "Example:\n" <<
                "    http-client-sync-ssl www.example.com 443 /\n" <<
                "    http-client-sync-ssl www.example.com 443 / 1.0\n" << 
                std::endl << optionDescription << std::endl;
            return EXIT_FAILURE;
        }*/
        auto const target = "/";

        // The io_context is required for all I/O
        boost::asio::io_context ioc;

        // The SSL context is required, and holds certificates
        ssl::context ctx{ssl::context::sslv23_client};

        // This holds the root certificate used for verification
        keto::ssl::load_root_certificates(ctx);

        /*// These objects perform our I/O
        tcp::resolver resolver{ioc};
        ssl::stream<tcp::socket> stream{ioc, ctx};

        // Set SNI Hostname (many hosts need this to handshake successfully)
        if(! SSL_set_tlsext_host_name(stream.native_handle(), host.c_str()))
        {
            boost::system::error_code ec{static_cast<int>(::ERR_get_error()), boost::asio::error::get_ssl_category()};
            throw boost::system::system_error{ec};
        }

        // Look up the domain name
        auto const results = resolver.resolve(host, port);

        // Make the connection on the IP address we get from a lookup
        boost::asio::connect(stream.next_layer(), results.begin(), results.end());

        // Perform the SSL handshake
        stream.handshake(ssl::stream_base::client);

        // Set up an HTTP GET request message
        http::request<http::string_body> req{http::verb::get, target, keto::cli::Constants::HTTP_VERSION};
        req.set(http::field::host, host);
        req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

        // Send the HTTP request to the remote host
        http::write(stream, req);

        // This buffer is used for reading and must be persisted
        boost::beast::flat_buffer buffer;

        // Declare a container to hold the response
        http::response<http::dynamic_body> res;

        // Receive the HTTP response
        http::read(stream, buffer, res);*/
        
        keto::session::HttpSession session(ioc,ctx,
                privateKey,publicKey);
        std::string result= 
                session.setHost(host).setPort(port).handShake().makeRequest("test");

        // Write the message to standard out
        std::cout << result << std::endl;

        // Gracefully close the stream
        //boost::system::error_code ec;
        //stream.shutdown(ec);
        //if(ec == boost::asio::error::eof)
        //{
        //    // Rationale:
        //    // http://stackoverflow.com/questions/25587403/boost-asio-ssl-async-shutdown-always-finishes-with-an-error
        //    ec.assign(0, ec.category());
        //}
        //if(ec)
        //    throw boost::system::system_error{ec};

        // If we get here then the connection is closed gracefully
        
        KETO_LOG_INFO << "CLI Executed";
    } catch (keto::common::Exception& ex) {
        KETO_LOG_ERROR << "Failed to start because : " << ex.what();
        KETO_LOG_ERROR << "Cause: " << boost::diagnostic_information(ex,true);
        return -1;
    } catch (boost::exception& ex) {
        KETO_LOG_ERROR << "Failed to start because : " << boost::diagnostic_information(ex,true);
        return -1;
    } catch (std::exception& ex) {
        KETO_LOG_ERROR << "Failed to start because : " << ex.what();
        return -1;
    } catch (...) {
        KETO_LOG_ERROR << "Failed to start unknown error.";
        return -1;
    }
}
