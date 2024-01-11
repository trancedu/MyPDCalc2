#pragma once
#include <string>
#include "publisher.h"
using std::string;


class UserInterface : protected Publisher
{
public:
	virtual void showMessage(const string& message) = 0;
	virtual void handleStackChanged() = 0;
	virtual void execute() = 0;
	static string commandEnteredEventName() { return "CommandEntered"; }
	using Publisher::attach;
	using Publisher::detach;
};