#pragma once
#include <memory>
#include <unordered_map>
#include "command.h"

class CommandFactory
{
public:
	CommandPtr allocateCommand(const string& commandName) {
		if (auto it = factory_.find(commandName); it != factory_.end()) {
			return MakeCommandPtr(it->second->clone());
		}
		return MakeCommandPtr(nullptr);
	}

	void registerCommand(const string& commandName, CommandPtr command) {
		//factory_[commandName] = std::move(command);
		factory_.insert({ commandName, std::move(command) });
	}

	void registerCommand(CommandPtr command) {
		//factory_[command->name()] = std::move(command);
		factory_.insert({ command->name(), std::move(command) });
	}

	static CommandFactory& Instance() {
		static CommandFactory factory;
		return factory;
	}
private:
	std::unordered_map<string, CommandPtr> factory_;
	CommandFactory() = default;
	CommandFactory(const CommandFactory&) = delete;
	CommandFactory& operator=(const CommandFactory&) = delete;
	CommandFactory(CommandFactory&&) = delete;
	CommandFactory& operator=(CommandFactory&&) = delete;
};


void registerCoreCommands() {
	CommandFactory& factory = CommandFactory::Instance();
	factory.registerCommand(MakeCommandPtr(new Add));
	factory.registerCommand(MakeCommandPtr(new Sine));
}

