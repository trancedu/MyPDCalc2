#include "pch.h"
#include "testdll.h"
//
//extern "C" MYPLUGIN_API double addOne(int x) {
//	return x + 1;
//}


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
