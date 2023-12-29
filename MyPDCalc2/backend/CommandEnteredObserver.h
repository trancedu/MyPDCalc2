#pragma once
#include "observer.h"
#include "CommandInterpreter.h"

class CommandEnteredObserver : public Observer
{
public:
	explicit CommandEnteredObserver(CommandInterpreter& ci) :
		ci_{ ci } {}
	string name() const override {
		return "CommandEnteredObserver";
	}
	void notify(const std::any& message) override {
		ci_.execute(any_cast<string>(message));
	}
private:
	CommandInterpreter& ci_;
};