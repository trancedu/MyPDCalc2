#pragma once
#include "command.h"
#include "export.h"

class BACKEND_API Plugin
{
public:
	Plugin();
	virtual ~Plugin();
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



