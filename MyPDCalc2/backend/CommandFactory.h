#pragma once
#include <memory>
#include <unordered_map>
#include "command.h"

class CommandFactory
{
public:
	unique_ptr<Command> allocateCommand(const string& commandName) {
		if (auto it = factory_.find(commandName); it != factory_.end()) {
			return std::move(it->second);
		}
	}

	void registerCommand(const string& commandName, std::unique_ptr<Command> command) {
		factory_[commandName] = std::move(command);
	}

	void registerCommand(std::unique_ptr<Command> command) {
		factory_[command->name()] = std::move(command);
	}

	static CommandFactory& Instance() {
		static CommandFactory factory;
		return factory;
	}
private:
	std::unordered_map<string, unique_ptr<Command>> factory_;
	CommandFactory() = default;
	CommandFactory(const CommandFactory&) = delete;
	CommandFactory& operator=(const CommandFactory&) = delete;
	CommandFactory(CommandFactory&&) = delete;
	CommandFactory& operator=(CommandFactory&&) = delete;
};


void registerCoreCommands() {
	CommandFactory& factory = CommandFactory::Instance();
	factory.registerCommand(std::make_unique<Add>());
	factory.registerCommand(std::make_unique<Sine>());
}