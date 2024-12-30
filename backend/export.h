#pragma once

#ifdef _WIN32
    #ifdef BACKEND_EXPORTS
        #define BACKEND_API __declspec(dllexport)
    #else
        #define BACKEND_API __declspec(dllimport)
    #endif
#else
    #define BACKEND_API
#endif 