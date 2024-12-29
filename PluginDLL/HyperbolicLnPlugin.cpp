#include "HyperbolicLnPlugin.h"


extern "C" void* AllocPlugin() {
    return new HyperbolicLnPlugin;
}

extern "C" void DeallocPlugin(void* p) {
    auto d = static_cast<Plugin*>(p);
    delete d;
}

extern "C" double addTwo(int x) {
    return x + 2;
}
