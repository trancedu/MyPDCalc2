#pragma once

#ifdef _WIN32
    #ifdef PLUGINDLL_EXPORTS
        #define MYPLUGIN_API __declspec(dllexport)
    #else
        #define MYPLUGIN_API __declspec(dllimport)
    #endif
#else
    #define MYPLUGIN_API
#endif 