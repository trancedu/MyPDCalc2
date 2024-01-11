#include "StackPluginInterface.h"
#include "stack.h"

Stack* g_stackInstance = nullptr;

void StackPush(double d, bool notify) {
	g_stackInstance->push(d, notify);
}

double StackPop(bool notify) {
	return g_stackInstance->pop(notify);
}

size_t StackSize() {
	return g_stackInstance->size();
}

double StackFirstElement() {
	return g_stackInstance->getElements(1)[0];
}

double StackSecondElement() {
	return g_stackInstance->getElements(2)[1];
}
