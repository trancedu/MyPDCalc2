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
		vector<double> data = Stack::Instance().getElements();
		std::ostringstream oss;
		for (const auto& num : data) {
			oss << num << "\t";
		}
		ui_.showMessage(oss.str());
	}
private:
	UserInterface& ui_;
};