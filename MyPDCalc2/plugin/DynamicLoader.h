#pragma once
#include <string>
using std::string;

class DynamicLoader
{
public:
	virtual ~DynamicLoader() = default;

	virtual class Plugin* allocatePlugin(const string& pluginName) = 0;
	virtual void deallocatePlugin(class Plugin*) = 0;

	static string GetPluginAllocationName() { return "AllocPlugin"; }
	static string GetPluginDeallocationName() { return "DeallocPlugin"; }
};


extern "C" {typedef void* (*PluginAllocator)(void); }
extern "C" {typedef void (*PluginDeallocator)(void*); }
