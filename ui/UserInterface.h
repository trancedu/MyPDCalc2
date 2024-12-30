#pragma once
#include <string>
#include "publisher.h"
#include "export.h"
using std::string;


class UI_API UserInterface : protected Publisher
{
public:
	virtual void showMessage(const string& message) = 0;
	virtual void handleStackChanged() = 0;
	virtual void execute() = 0;
	static string commandEnteredEventName();
	using Publisher::attach;
	using Publisher::detach;
};