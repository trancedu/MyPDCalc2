#include "PosixFactory.h"
#include "PosixDynamicLoader.h"

PosixFactory::PosixFactory()
{
}

std::unique_ptr<DynamicLoader> PosixFactory::createDynamicLoader()
{
    return std::make_unique<PosixDynamicLoader>();
}