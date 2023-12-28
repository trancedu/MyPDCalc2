#pragma once
#include <string>
#include "publisher.h"
using std::string;


class UserInterface : private Publisher
{
public:
	virtual void showMessage(const string& message) = 0;
	virtual void handleStackChanged() = 0;
	static string commandEnteredEventName() { return "CommandEntered"; }
	using Publisher::attach;
	using Publisher::detach;
};