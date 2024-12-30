#pragma once
#include "stack.h"
#include "export.h"

extern "C" BACKEND_API void StackPush(double d, bool notify);

extern "C" BACKEND_API double StackPop(bool notify);

extern "C" BACKEND_API size_t StackSize();

extern "C" BACKEND_API double StackFirstElement();

extern "C" BACKEND_API double StackSecondElement();

