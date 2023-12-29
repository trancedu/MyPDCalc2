#pragma once
#include "command.h"
class Plugin
{
public:
	Plugin() = default;
	virtual ~Plugin() = default;
	struct PluginDescriptor
	{
		int nCommands;
		char** commandNames;
		Command** commands;
	};
	virtual const PluginDescriptor& getPluginDescriptor() const = 0;
};

