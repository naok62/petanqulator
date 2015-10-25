#ifndef _UTILS_HPP_
#define _UTILS_HPP_

#define _USE_MATH_DEFINES
#include <cmath>

#include <iostream>
#include <string>

#define EPSILON 1e-6
#define INFINI 1e6
#define EGAL(a,b) (fabs( (a) - (b)) < EPSILON)
#define PROCHE(a,b, e) (fabs( (a) - (b)) < (e))

#define UTILS_ERROR(msg) \
{ \
    std::cerr << "error: " << msg  \
        << " (" << __FILE__ << ' ' << __LINE__ << ")" << std::endl; \
    exit(-1); \
} 

#define UTILS_INFO(msg) \
{ \
    std::clog << "info: " << msg  \
        << " (" << __FILE__ << ' ' << __LINE__ << ")" << std::endl; \
} 

#endif
