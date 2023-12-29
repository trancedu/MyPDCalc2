#pragma once
#include <vector>
#include "publisher.h"
using std::vector;

class Stack : private Publisher
{
public:
	void push(double num, bool notify = true);
	double pop(bool notify = true);
	void clear();
	int size();
	vector<double> getElements(int n = 4);
	static Stack& Instance();
	static string stackChangedEventName();
	using Publisher::attach;
	using Publisher::detach;
private:
	Stack() = default;
	Stack(const Stack&) = delete;
	Stack& operator=(const Stack&) = delete;
	Stack(Stack&&) = delete;
	Stack& operator=(Stack&&) = delete;
	void raiseStackChangedEvent();
	vector<double> data_;
};