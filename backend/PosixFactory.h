#pragma once
#include "PlatformFactory.h"
#include <memory>

class PosixFactory : public PlatformFactory
{
public:
    PosixFactory();
    std::unique_ptr<DynamicLoader> createDynamicLoader() override;
};