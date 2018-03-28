/*
 * This class provides utils to transform to and from secure vectors and traditional
 * std::vectors. There are probably cleaner ways of handling this transformation,
 * if you know of them please supply suggestions or make changes in the implementation
 * class.
 */

/* 
 * File:   SecureVectorUtils.hpp
 * Author: ubuntu
 *
 * Created on February 16, 2018, 11:42 AM
 */

#ifndef SECUREVECTORUITLS_HPP
#define SECUREVECTORUITLS_HPP

#include <vector>
#include "keto/crypto/Containers.hpp"

namespace keto {
namespace crypto {

class SecureVectorUtils {
public:
    SecureVectorUtils();
    SecureVectorUtils(const SecureVectorUtils& orig) = default;
    virtual ~SecureVectorUtils();
    
    
    std::vector<uint8_t> copyFromSecure(const SecureVector& secureVector);
    std::vector<uint8_t> copyFromSecure(SecureVector& secureVector);
    SecureVector copyToSecure(const std::vector<uint8_t>& vector);
    SecureVector copyToSecure(std::vector<uint8_t>& vector);
    
    SecureVector copyStringToSecure(const std::string& str);
    std::string copySecureToString(const SecureVector& vec);
private:

};


}
}


#endif /* SECUREVECTORUITLS_HPP */

