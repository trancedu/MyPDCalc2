# pragma once
#include "CLI.h"
#include "stack.h"
#include "stackChangedObserver.h"
#include "CommandEnteredObserver.h"
#include "CommandFactory.h"
#include "PluginLoader.h"
using std::make_unique;

void setupUi(UserInterface& ui, CommandInterpreter& ci)
{
	registerCoreCommands();

	ui.attach(UserInterface::commandEnteredEventName(), make_unique<CommandEnteredObserver>(ci));

	Stack::Instance().attach(Stack::stackChangedEventName(), make_unique<StackChangedObserver>(ui));
}

int main()
{
	CLI cli{ std::cin, std::cout };
	PluginLoader loader;
	CommandInterpreter ci{ cli };
	setupUi(cli, ci);
	set<string> injectedCommands{ setupPlugins(cli, loader) };
	cli.execute();
	ranges::for_each(injectedCommands, [](auto i) {CommandFactory::Instance().deregisterCommand(i); });
	return 0;
}