#pragma once
#include "stack.h"
extern Stack* g_stackInstance;

extern "C" void StackPush(double d, bool notify);

extern "C" double StackPop(bool notify);

extern "C" size_t StackSize();

extern "C" double StackFirstElement();

extern "C" double StackSecondElement();

