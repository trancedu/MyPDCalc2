#pragma once
#include <string>
#include <sstream>
#include <format>
#include "stack.h"
#include "UserInterface.h"
#include "exception.h"
#include "CommandManager.h"
#include "CommandFactory.h"

class CommandInterpreter
{
public:
	explicit CommandInterpreter(UserInterface& ui) : ui_{ ui }, manager_{ ui } {}
	void execute(const string& command) {
		if (double d; isNum(command, d)) {
			manager_.execute(MakeCommandPtr(new EnterNumber{d}));
		}
		else if (command == "undo") {
			manager_.undo();
		}
		else if (command == "redo") {
			manager_.redo();
		}
		else {
			try {
				CommandPtr cmd = CommandFactory::Instance().allocateCommand(command);
				if (!cmd) { 
					ui_.showMessage(std::format("The command {} is not recognized", command)); 
				}
				manager_.execute(std::move(cmd));
			}
			catch (const Exception& e) {
				ui_.showMessage(std::format("Error in Executing commands: {}", e.what()));
			}
		}
	}
private:
	bool isNum(const string& command, double& num) const {
		std::istringstream iss{ command };
		iss >> num;
		if (iss.fail() || !iss.eof()) {
			return false;
		}
		return true;
	}
	UserInterface& ui_;
	CommandManager manager_;
};