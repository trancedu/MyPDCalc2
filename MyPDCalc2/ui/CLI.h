#pragma once
#include <iostream>
#include "UserInterface.h"

class CLI : public UserInterface
{
public:
	explicit CLI(std::istream& in, std::ostream& out) : in_{ in }, out_{ out } {}
	CLI() = default;
	void showMessage(const string& message) override {
		out_ << message << '\n';
	}

	void handleStackChanged() override {
		// out_ << stack top elements << '\n';
	}
private:
	std::istream& in_;
	std::ostream& out_;
};