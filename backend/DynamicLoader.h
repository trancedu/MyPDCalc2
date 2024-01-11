#pragma once
#include <string>
#include "stack.h"
using std::string;


class DynamicLoader
{
public:
	virtual ~DynamicLoader() = default;

	virtual class Plugin* allocatePlugin(const string& pluginName) = 0;
	virtual void deallocatePlugin(class Plugin*) = 0;

	static string GetPluginAllocationName() { return "AllocPlugin"; }
	static string GetPluginDeallocationName() { return "DeallocPlugin"; }

	virtual void setStackInDLL() = 0;
	static string GetSetStackInDLLName() { return "DLL_SetStackInstance"; }
};


extern "C" {typedef void* (*PluginAllocator)(void); }
extern "C" {typedef void (*PluginDeallocator)(void*); }
extern "C" {typedef void (*SetStackFunc)(void*); }