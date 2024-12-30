#pragma once
#include <iostream>
#include "UserInterface.h"
#include "Tokenizer.h"
#include "CommandInterpreter.h"

class CLI : public UserInterface
{
public:
	explicit CLI(std::istream& in, std::ostream& out);
	CLI() = delete;
	void showMessage(const string& message) override;

	void handleStackChanged() override;

	void execute() override;

private:
	std::istream& in_;
	std::ostream& out_;
};