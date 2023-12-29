#pragma once
#include <string>
#include <sstream>
#include <format>
#include "stack.h"
#include "UserInterface.h"
#include "exception.h"

class CommandInterpreter
{
public:
	explicit CommandInterpreter(UserInterface& ui) : ui_{ ui } {}
	void execute(const string& command) {
		if (double d; isNum(command, d)) {
			Stack::Instance().push(d);
			//manager_.executeCommand(std::make_unique<EnterCommand>(d));
		}
		else if (command == "undo") {
			//commandManager.undo();
		}
		else if (command == "redo") {
			//commandManager.redo();
		}
		else {
			try {
				//std::unique_ptr<Command> cmd = CommandFactory::Instance().allocateCommand(command));
			}
			catch (const Exception& e) {
				ui_.showMessage(std::format("The command {} is not recognized", command));
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
	//CommandManager manager_;
};