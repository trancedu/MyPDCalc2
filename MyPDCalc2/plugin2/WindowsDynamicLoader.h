#pragma once
#include <windows.h>
#include "DynamicLoader.h"
#include "exception.h"

class WindowsDynamicLoader : public DynamicLoader
{
public:
	WindowsDynamicLoader() :DynamicLoader{}, handle_{ nullptr } {}
	~WindowsDynamicLoader() {
		if (handle_) FreeLibrary(handle_);
	}

	Plugin* allocatePlugin(const string& pluginName) override {
		handle_ = LoadLibraryA(pluginName.c_str());
		if (!handle_) return nullptr;
		else {
			auto alloc = GetProcAddress(handle_, GetPluginAllocationName().c_str());
			if (PluginAllocator allocator{ reinterpret_cast<PluginAllocator>(alloc) }) {
				auto p = static_cast<Plugin*>((*allocator)());
				return p;
			}
			else return nullptr;
		}
	}

	void setStackInDLL() override {
		if (!handle_) {
			throw Exception("Trying to set Stack in DLL, but shared library is not open");
		}
		else {
			auto func = GetProcAddress(handle_, GetSetStackInDLLName().c_str());
			if (auto f = reinterpret_cast<SetStackFunc>(func)) {
				(*f)(&Stack::Instance());
			}
			else throw Exception("Could not set stack in the plugin");
		}
		return;
	}

	void deallocatePlugin(Plugin* p) override {
		if (!handle_) {
			throw Exception("Trying to deallocate a plugin, but shared library is not open");
		}
		else {
			auto dealloc = GetProcAddress(handle_, GetPluginDeallocationName().c_str());
			if (auto deallocator = reinterpret_cast<PluginDeallocator>(dealloc)) {
				(*deallocator)(p);
			}
			else throw Exception("Could not load the deallocator function in the plugin");
		}
		return;
	}
private:
	HINSTANCE handle_;
};

