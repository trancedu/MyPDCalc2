#pragma once

#ifdef _WIN32
    #ifdef UTILITIES_EXPORTS
        #define UTILITIES_API __declspec(dllexport)
    #else
        #define UTILITIES_API __declspec(dllimport)
    #endif
#else
    #define UTILITIES_API
#endif 