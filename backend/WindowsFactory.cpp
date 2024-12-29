#include "WindowsFactory.h"
#include "WindowsDynamicLoader.h"

WindowsFactory::WindowsFactory()
{ }

std::unique_ptr<DynamicLoader> WindowsFactory::createDynamicLoader()
{
    return std::make_unique<WindowsDynamicLoader>();
}