#pragma once
#include <vector>
#include <ranges>
#include "UserInterface.h"
#include "plugin.h"
#include "CommandFactory.h"
#include "DynamicLoader.h"
#include <fstream>
#include <iterator>
#include <algorithm>
#include <memory>
#include <ranges>
#include <vector>
#include <string>
#include <format>
#include <set>
#include "WindowsDynamicLoader.h"
using std::vector;
using std::string;
using std::ifstream;
using std::unique_ptr;
using std::format;
using std::set;
namespace ranges = std::ranges;
class PluginDeleter
{
public:
	explicit PluginDeleter(DynamicLoader& d) : loader_{ d } {}
	void operator()(Plugin* p){loader_.deallocatePlugin(p); }
private:
	DynamicLoader& loader_;
};

class PluginLoader
{
public:
	PluginLoader() = default;
	~PluginLoader() = default;

	void loadPlugins(UserInterface& ui, const string& pluginFileName);
	const vector<const Plugin*> getPlugins() const {
		vector<const Plugin*> v;
		for (auto& i : plugins_) {
			v.push_back(i.get());
		}
		return v;
	}

private:
	PluginLoader(const PluginLoader&) = delete;
	PluginLoader(PluginLoader&&) = delete;
	PluginLoader& operator=(const PluginLoader&) = delete;
	PluginLoader& operator=(PluginLoader&&) = delete;

	void load(UserInterface& ui, const string& name) {
		loaders_.emplace_back(new WindowsDynamicLoader{});
		if (auto p = loaders_.back()->allocatePlugin(name)) {
			plugins_.emplace_back(p, PluginDeleter(*loaders_.back()));
		}
		else {
			ui.showMessage(format("Error opening plugin: {}", name));
		}
	}

	vector<unique_ptr<DynamicLoader>> loaders_;
	vector<unique_ptr<Plugin, PluginDeleter>> plugins_;
};

void PluginLoader::loadPlugins(UserInterface& ui, const string& pluginFileName)
{
	if (ifstream ifs{ pluginFileName.c_str() })
	{
		ranges::for_each(vector<string>{std::istream_iterator<string>(ifs), std::istream_iterator<string>()},
			[&ui, this](auto n) {load(ui, n); });
	}
	else {
		ui.showMessage("Could not open plugin file");
	}
}


void registerCommand(UserInterface& ui, const string& label, CommandPtr c)
{
	try
	{
		CommandFactory::Instance().registerCommand(label, std::move(c));
	}
	catch (Exception& e)
	{
		ui.showMessage(e.what());
	}

	return;
}

set<string> setupPlugins(UserInterface& ui, PluginLoader& loader)
{
	loader.loadPlugins(ui, "plugins.pdp");
	auto plugins = loader.getPlugins();
	
	set<string> injectedCommands;
	for (auto p : plugins)
	{
		auto apiVersion = p->apiVersion();
		auto& descriptor = p->getPluginDescriptor();
		for (auto i : std::views::iota(0, descriptor.nCommands))
		{
			registerCommand(ui, descriptor.commandNames[i],
				MakeCommandPtr(descriptor.commands[i]->clone()));
			injectedCommands.insert(descriptor.commandNames[i]);
		}
	}
	return injectedCommands;
}