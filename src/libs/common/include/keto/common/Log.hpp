/* 
 * File:   Log.h
 * Author: Brett Chaldecott
 *
 * Created on January 12, 2018, 7:32 AM
 */

#ifndef LOG_H
#define LOG_H

#include <boost/log/trivial.hpp>

namespace keto {
namespace common {

// keto logging macros
#define KETO_LOG_TRACE \
   BOOST_LOG_TRIVIAL(trace)
#define KETO_LOG_DEBUG \
   BOOST_LOG_TRIVIAL(debug)
#define KETO_LOG_INFO \
   BOOST_LOG_TRIVIAL(info)
#define KETO_LOG_WARNING \
   BOOST_LOG_TRIVIAL(warning)
#define KETO_LOG_ERROR \
   BOOST_LOG_TRIVIAL(error)
#define KETO_LOG_FATAL \
   BOOST_LOG_TRIVIAL(fatal)

}
}

#endif /* LOG_H */

