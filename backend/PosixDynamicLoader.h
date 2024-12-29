#pragma once
#include <dlfcn.h> // POSIX dynamic linking functions
#include "DynamicLoader.h"
#include "exception.h"

class PosixDynamicLoader : public DynamicLoader
{
public:
    PosixDynamicLoader() : DynamicLoader{}, handle_{ nullptr } {}
    ~PosixDynamicLoader() {
        if (handle_) dlclose(handle_);
    }

    Plugin* allocatePlugin(const string& pluginName) override {
        // Open the dynamic library
        handle_ = dlopen(pluginName.c_str(), RTLD_LAZY);
        if (!handle_) {
            return nullptr; // Failed to open library
        } else {
            // Load the plugin allocation function
            void* alloc = dlsym(handle_, GetPluginAllocationName().c_str());
            if (PluginAllocator allocator = reinterpret_cast<PluginAllocator>(alloc)) {
                // Call the allocator to allocate the plugin
                return static_cast<Plugin*>((*allocator)());
            } else {
                return nullptr; // Allocation function not found
            }
        }
    }

    void setStackInDLL() override {
        if (!handle_) {
            throw Exception("Trying to set Stack in DLL, but shared library is not open");
        } else {
            // Load the function to set the stack
            void* func = dlsym(handle_, GetSetStackInDLLName().c_str());
            if (auto f = reinterpret_cast<SetStackFunc>(func)) {
                // Call the function and pass the Stack instance
                (*f)(&Stack::Instance());
            } else {
                throw Exception("Could not set stack in the plugin");
            }
        }
    }

    void deallocatePlugin(Plugin* p) override {
        if (!handle_) {
            throw Exception("Trying to deallocate a plugin, but shared library is not open");
        } else {
            // Load the plugin deallocation function
            void* dealloc = dlsym(handle_, GetPluginDeallocationName().c_str());
            if (auto deallocator = reinterpret_cast<PluginDeallocator>(dealloc)) {
                // Call the deallocator to clean up the plugin
                (*deallocator)(p);
            } else {
                throw Exception("Could not load the deallocator function in the plugin");
            }
        }
    }

private:
    void* handle_; // Handle to the dynamic library (dlopen/dlclose)
};
