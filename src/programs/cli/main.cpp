
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
#include "keto/common/StringCodec.hpp"
#include "keto/environment/EnvironmentManager.hpp"
#include "keto/environment/Constants.hpp"
#include "keto/ssl/RootCertificate.hpp"
#include "keto/cli/Constants.hpp"
#include "keto/session/HttpSession.hpp"

#include "keto/chain_common/TransactionBuilder.hpp"
#include "keto/chain_common/SignedTransactionBuilder.hpp"
#include "keto/chain_common/ActionBuilder.hpp"
#include "keto/transaction_common/TransactionMessageHelper.hpp"

#include "keto/account_utils/AccountGenerator.hpp"

namespace ketoEnv = keto::environment;
namespace ketoCommon = keto::common;
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
namespace ssl = boost::asio::ssl;       // from <boost/asio/ssl.hpp>
namespace http = boost::beast::http;    // from <boost/beast/http.hpp>

boost::program_options::options_description generateOptionDescriptions() {
    boost::program_options::options_description optionDescripion;
    
    optionDescripion.add_options()
            ("help,h", "Print this help message and exit.")
            ("version,v", "Print version information.")
            ("accgen,A", "Generate an account.")
            ("account_key,K", po::value<std::string>(),"Private key file.")
            ("transgen,T", "Generate a transaction.")
            ("action,a", po::value<std::string>(),"Action Hash or Name.")
            ("parent,p", po::value<std::string>(),"Parent Transaction.")
            ("source,s", po::value<std::string>(),"Source Account Hash.")
            ("target,t",po::value<std::string>(), "Target Account Hash.")
            ("value,V", po::value<long>(), "Value of the transaction.");
    
    return optionDescripion;
}

std::shared_ptr<keto::chain_common::TransactionBuilder> buildTransaction(
        const std::string& contractHash, const std::string& parentHash,
        const std::string& accountHash, const std::string& targetHash,
        const long value) {
    
    std::shared_ptr<keto::chain_common::ActionBuilder> actionPtr =
            keto::chain_common::ActionBuilder::createAction();
    actionPtr->setContract(
            keto::asn1::HashHelper(contractHash,
                keto::common::HEX)).setParent(
            keto::asn1::HashHelper(parentHash,
                keto::common::HEX));
    
    long longValue = value;
    
    std::shared_ptr<keto::chain_common::TransactionBuilder> transactionPtr =
        keto::chain_common::TransactionBuilder::createTransaction();
    transactionPtr->setParent(
            keto::asn1::HashHelper(parentHash,
        keto::common::HEX)).setSourceAccount(
            keto::asn1::HashHelper(accountHash,
        keto::common::HEX)).setTargetAccount(
            keto::asn1::HashHelper(targetHash,
        keto::common::HEX)).setValue(keto::asn1::NumberHelper(longValue)).addAction(actionPtr);
    
    return transactionPtr;
}

int generateTransaction(std::shared_ptr<ketoEnv::Config> config,
        boost::program_options::options_description optionDescription) {
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

    // read in the keys
    keto::crypto::KeyLoader keyLoader(privateKey, publicKey);

    // retrieve the action hash
    if (!config->getVariablesMap().count(keto::cli::Constants::ACTION)) {
        std::cerr << "Please provide the action name or hash [" << 
                keto::cli::Constants::ACTION << "]" << std::endl;
        std::cout <<  optionDescription << std::endl;
        return -1;
    }
    std::string action = config->getVariablesMap()[keto::cli::Constants::ACTION].as<std::string>();
    if (config->getVariablesMap().count(action)) {
        action = config->getVariablesMap()[action].as<std::string>();
    }

    // retrieve the parent hash
    if (!config->getVariablesMap().count(keto::cli::Constants::PARENT)) {
        std::cerr << "Please provide the parent hash [" << 
                keto::cli::Constants::PARENT << "]" << std::endl;
        std::cout <<  optionDescription << std::endl;
        return -1;
    }
    std::string parentHash = config->getVariablesMap()[keto::cli::Constants::PARENT].as<std::string>();

    // retrieve source account hash
    if (!config->getVariablesMap().count(keto::cli::Constants::SOURCE_ACCOUNT)) {
        std::cerr << "Please provide the source account [" << 
                keto::cli::Constants::SOURCE_ACCOUNT << "]" << std::endl;
        std::cout <<  optionDescription << std::endl;
        return -1;
    }
    std::string sourceAccount = config->getVariablesMap()[keto::cli::Constants::SOURCE_ACCOUNT].as<std::string>();

    // retrieve target account hash
    if (!config->getVariablesMap().count(keto::cli::Constants::TARGET_ACCOUNT)) {
        std::cerr << "Please provide the target account [" << 
                keto::cli::Constants::TARGET_ACCOUNT << "]" << std::endl;
        std::cout <<  optionDescription << std::endl;
        return -1;
    }
    std::string targetAccount = config->getVariablesMap()[keto::cli::Constants::TARGET_ACCOUNT].as<std::string>();
    
    // retrieve transaction value
    if (!config->getVariablesMap().count(keto::cli::Constants::VALUE)) {
        std::cerr << "Please provide the value [" << 
                keto::cli::Constants::VALUE << "]" << std::endl;
        std::cout <<  optionDescription << std::endl;
        return -1;
    }
    long value = config->getVariablesMap()[keto::cli::Constants::VALUE].as<long>();


    std::shared_ptr<keto::chain_common::TransactionBuilder> transactionPtr = buildTransaction(
        action, parentHash,sourceAccount, targetAccount,value);

    keto::asn1::PrivateKeyHelper privateKeyHelper;
    privateKeyHelper.setKey(
        Botan::PKCS8::BER_encode( *keyLoader.getPrivateKey() ));

    std::shared_ptr<keto::chain_common::SignedTransactionBuilder> signedTransBuild = 
        keto::chain_common::SignedTransactionBuilder::createTransaction(
            privateKeyHelper);
    
    
    signedTransBuild->setTransaction(transactionPtr);
    signedTransBuild->sign();
    
    keto::transaction_common::TransactionMessageHelperPtr transactionMessageHelperPtr(
        new keto::transaction_common::TransactionMessageHelper(
        *signedTransBuild));
    
    // The io_context is required for all I/O
    boost::asio::io_context ioc;

    // The SSL context is required, and holds certificates
    ssl::context ctx{ssl::context::sslv23_client};

    // This holds the root certificate used for verification
    keto::ssl::load_root_certificates(ctx);

    keto::session::HttpSession session(ioc,ctx,
            privateKey,publicKey);
    std::string result= 
            session.setHost(host).setPort(port).handShake().makeRequest(
            transactionMessageHelperPtr);

    // Write the message to standard out
    std::cout << result << std::endl;
    return 0;
}

int generateAccount(std::shared_ptr<ketoEnv::Config> config,
        boost::program_options::options_description optionDescription) {
    if (config->getVariablesMap().count(keto::cli::Constants::KETO_ACCOUNT_KEY)) {
        std::string keyPath = config->getVariablesMap()[keto::cli::Constants::KETO_ACCOUNT_KEY].as<std::string>();
        std::cout << ((const std::string)keto::account_utils::AccountGenerator(keyPath)) << std::endl;
    } else {
        std::cout << ((const std::string)keto::account_utils::AccountGenerator()) << std::endl;
    }
    return 0;
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
        
        if (config->getVariablesMap().count(keto::cli::Constants::KETO_TRANSACTION_GEN)) 
        {
            return generateTransaction(config,optionDescription);
        } else if (config->getVariablesMap().count(keto::cli::Constants::KETO_ACCOUNT_GEN)) {
            return generateAccount(config,optionDescription);
        }
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
