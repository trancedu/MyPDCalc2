#pragma once
#include "PlatformFactory.h"
#include <memory>

class WindowsFactory : public PlatformFactory
{
public:
    WindowsFactory();

    std::unique_ptr<DynamicLoader> createDynamicLoader() override;
};