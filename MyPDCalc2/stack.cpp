#include "stack.h"

void Stack::push(double num, bool notify) {
	data_.push_back(num);
	if (notify) {
		raiseStackChangedEvent();
	}
}

void Stack::pop(bool notify) {
	data_.pop_back();
	if (notify) {
		raiseStackChangedEvent();
	}
}

void Stack::clear() {
	data_.clear();
	raiseStackChangedEvent();
}

vector<double> Stack::getElements(int n) {
	if (data_.size() < n) {
		return data_;
	}
	return vector<double>(data_.end() - n, data_.end());
}

Stack& Stack::Instance() {
	static Stack stack;
	return stack;
}

string Stack::stackChangedEventName() { return "StackChanged"; }

void Stack::raiseStackChangedEvent() {
	raise(stackChangedEventName(), "");
}
