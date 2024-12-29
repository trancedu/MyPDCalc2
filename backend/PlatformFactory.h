#pragma once
#include <memory>

class DynamicLoader;

class PlatformFactory
{
public:
    static PlatformFactory& Instance();
    virtual ~PlatformFactory();

    virtual std::unique_ptr<DynamicLoader> createDynamicLoader() = 0;

protected:
    PlatformFactory();

private:
    PlatformFactory(const PlatformFactory&) = delete;
    PlatformFactory& operator=(const PlatformFactory&) = delete;
    PlatformFactory(PlatformFactory&&) = delete;
    PlatformFactory& operator=(PlatformFactory&&) = delete;
};
