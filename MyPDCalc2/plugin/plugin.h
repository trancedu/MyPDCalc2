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
	struct ApiVersion
	{
		int major;
		int minor;
	};
	virtual const PluginDescriptor& getPluginDescriptor() const = 0;
	virtual const ApiVersion apiVersion() const = 0;
};



