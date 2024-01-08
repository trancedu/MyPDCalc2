#pragma once
#include "stack.h"
extern "C" void StackPush(double d, bool notify) {
	Stack::Instance().push(d, notify);
}

extern "C" double StackPop(bool notify) {
	Stack::Instance().pop(notify);
}

extern "C" size_t StackSize() {
	return Stack::Instance().size();
}

extern "C" double StackFirstElement() {
	return Stack::Instance().getElements(1)[0];
}

extern "C" double StackSecondElement() {
	return Stack::Instance().getElements(2)[1];
}
