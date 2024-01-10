#include "pch.h"
#include "HyperbolicLnPlugin.h"


extern "C" MYPLUGIN_API void* AllocPlugin() {
    return new HyperbolicLnPlugin;
}

extern "C" MYPLUGIN_API void DeallocPlugin(void* p) {
    auto d = static_cast<Plugin*>(p);
    delete d;
}

extern "C" MYPLUGIN_API double addTwo(int x) {
    return x + 2;
}

MYPLUGIN_API void DLL_SetStackInstance(void* stackInstance)
{
    auto p = static_cast<Stack*>(stackInstance);
    g_stackInstance = p;
}
