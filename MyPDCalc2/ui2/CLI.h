#pragma once
#include <iostream>
#include "UserInterface.h"
#include "Tokenizer.h"
#include "CommandInterpreter.h"

class CLI : public UserInterface
{
public:
	explicit CLI(std::istream& in, std::ostream& out) : in_{ in }, out_{ out } {}
	CLI() = default;
	void showMessage(const string& message) override {
		out_ << "Message: " << message << '\n';
	}

	void handleStackChanged() override {
		out_ << "Stack: ";
		vector<double> data = Stack::Instance().getElements();
		for (const auto d : data) {
			out_ << d << '\t';
		}
		out_ << '\n';
	}

	void execute() override {
		for (string line; std::getline(in_, line, '\n');) {
			std::istringstream iss{ line };
			Tokenizer tokenizer{ iss };
			for (const string& token : tokenizer) {
				if (token == "exit") return;
				raise(commandEnteredEventName(), token);
			}
		}
	}

private:
	std::istream& in_;
	std::ostream& out_;
};