#include "command.h"

PluginCommand::PluginCommand() = default;
PluginCommand::~PluginCommand() = default;

void PluginCommand::checkPrecondition() const
{
    if (const char* p = checkPluginPreconditions())
        throw Exception(p);
}

PluginCommand* PluginCommand::clone() const
{
    if (auto p = clonePluginImpl())
        return p;
    else
        throw Exception("Problem cloning a plugin command");
} 