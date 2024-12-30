#include "PlatformFactory.h"
#ifdef _WIN32
#include "WindowsFactory.h"
#elif __APPLE__
#include "PosixFactory.h"
#else
#error "Unsupported platform"
#endif

PlatformFactory::PlatformFactory() = default;
PlatformFactory::~PlatformFactory() = default;

PlatformFactory& PlatformFactory::Instance() {
#ifdef _WIN32
    static WindowsFactory instance;
#elif __APPLE__
    static PosixFactory instance;
#else
    #error "Unsupported platform"
#endif
    return instance;
}