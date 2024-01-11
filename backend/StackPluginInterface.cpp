#include "StackPluginInterface.h"
#include "stack.h"

Stack* g_stackInstance = nullptr; // Not used in dev_singleton_conflict branch

void StackPush(double d, bool notify) {
	Stack::Instance().push(d, notify);
}

double StackPop(bool notify) {
	return Stack::Instance().pop(notify);
}

size_t StackSize() {
	return Stack::Instance().size();
}

double StackFirstElement() {
	return Stack::Instance().getElements(1)[0];
}

double StackSecondElement() {
	return Stack::Instance().getElements(2)[1];
}
