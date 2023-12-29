#pragma once
#include "observer.h"
#include "stack.h"
#include "UserInterface.h"
#include <sstream>

class StackChangedObserver : public Observer
{
public:
	StackChangedObserver(UserInterface& ui) : ui_{ ui } {}
	string name() const { return "StackChangedObserver"; }
	void notify(const std::any& message) override {
		ui_.handleStackChanged();
	}
private:
	UserInterface& ui_;
};