# pragma once
#include "CLI.h"
#include "stack.h"
#include "stackChangedObserver.h"
#include "CommandEnteredObserver.h"
int main()
{
	CLI cli{ std::cin, std::cout };
	CommandInterpreter ci{ cli };
	cli.attach("CommandEntered", std::make_unique<CommandEnteredObserver>(ci));
	Stack::Instance().attach("StackChanged", std::make_unique<StackChangedObserver>(cli));
	return 0;
}