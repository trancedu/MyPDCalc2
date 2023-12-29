#pragma once
#include <algorithm>
#include "CommandFactory.h"
#include "UserInterface.h"

class CommandManager
{
public:
	CommandManager(UserInterface& ui) : ui_{ ui }, commands(100, nullptr) {}
	void execute(unique_ptr<Command> command) {
		command->execute();
		commands[position_] = std::move(command);
		position_++;
	}
	void undo() {
		position_--;
		if (position_ >= 0) {
			commands[position_]->undo();
		}
		else {
			position_ = 0;
		}
	}
	void redo() {
		if (commands[position_]) {
			commands[position_]->execute();
			std::fill(commands.begin() + position_ + 1, commands.end(), nullptr);
		}
	}
private:
	UserInterface& ui_;
	std::vector<unique_ptr<Command>> commands;
	int position_ = 0;
};