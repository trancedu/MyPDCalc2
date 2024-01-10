//#pragma once
//#ifdef PLUGINDLL_EXPORTS
//#define MYPLUGIN_API __declspec(dllexport)
//#else
//#define MYPLUGIN_API __declspec(dllimport)
//#endif
//extern "C" MYPLUGIN_API double addOne(int x);

#pragma once
#ifdef PLUGINDLL_EXPORTS
#define MYPLUGIN_API __declspec(dllexport)
#else
#define MYPLUGIN_API __declspec(dllimport)
#endif

#include <iostream>
#include <ranges>
#include "plugin.h"
#include "command.h"
#include "StackPluginInterface.h"

using std::cout;
using std::endl;

using std::vector;
using std::string;
using std::unique_ptr;

extern "C" MYPLUGIN_API void* AllocPlugin();
extern "C" MYPLUGIN_API void DeallocPlugin(void* p);
extern "C" MYPLUGIN_API double addTwo(int x);

class MYPLUGIN_API HyperbolicLnPlugin : public Plugin
{
public:
    HyperbolicLnPlugin() {
        createPluginDescriptor();
    }
    ~HyperbolicLnPlugin() = default;
private:
    const PluginDescriptor& getPluginDescriptor() const override { return pd_; }
    const ApiVersion apiVersion() const override { return { 1, 0 }; }
    void createPluginDescriptor();
    HyperbolicLnPlugin(const HyperbolicLnPlugin&) = delete;
    HyperbolicLnPlugin& operator=(const HyperbolicLnPlugin&) = delete;
    HyperbolicLnPlugin(HyperbolicLnPlugin&&) = delete;
    HyperbolicLnPlugin& operator=(HyperbolicLnPlugin&&) = delete;
    PluginDescriptor pd_;
    vector<Command*> rawCommands_;
    vector<unique_ptr<Command>> commands_;
    vector<string> commandNames_;
    vector<char*> rawNames_;
};


class MYPLUGIN_API HyperbolicLnPluginCommand : public PluginCommand
{
public:
    HyperbolicLnPluginCommand() = default;
    explicit HyperbolicLnPluginCommand(const HyperbolicLnPluginCommand& rhs);
    virtual ~HyperbolicLnPluginCommand() = default;
    void deallocate() override;

protected:
    const char* checkPluginPreconditions() const noexcept override;

private:
    void executeImpl() noexcept override;

    // drops the result and returns the original number to the stack
    void undo() noexcept override;

    HyperbolicLnPluginCommand* clonePluginImpl() const noexcept override;
    virtual HyperbolicLnPluginCommand* doClone() const = 0;

    virtual double unaryOperation(double top) const = 0;

    double top_ = 0;
};

void HyperbolicLnPluginCommand::deallocate()
{
    delete this;
}

HyperbolicLnPluginCommand::HyperbolicLnPluginCommand(const HyperbolicLnPluginCommand& rhs)
    : PluginCommand(rhs)
    , top_(rhs.top_)
{
}

const char* HyperbolicLnPluginCommand::checkPluginPreconditions() const  noexcept
{
    if (StackSize() < 1)
        return "Stack must have one element";
    else return nullptr;
}

void HyperbolicLnPluginCommand::executeImpl() noexcept
{
    // suppress change signal so only one event raised for the execute
    top_ = StackPop(true);
    StackPush(unaryOperation(top_), false);

    return;
}

void HyperbolicLnPluginCommand::undo() noexcept
{
    // suppress change signal so only one event raised for the execute
    StackPop(true);
    StackPush(top_, false);

    return;
}

HyperbolicLnPluginCommand* HyperbolicLnPluginCommand::clonePluginImpl() const noexcept
{
    HyperbolicLnPluginCommand* p;
    try
    {
        p = doClone();
    }
    catch (...)
    {
        return nullptr;
    }

    return p;
}

// takes the hyperbolic sine of a number on the stack
// precondition: at least one number on the stack
class MYPLUGIN_API Sinh : public HyperbolicLnPluginCommand
{
public:
    Sinh() = default;
    explicit Sinh(const Sinh&);
    ~Sinh() = default;

private:
    Sinh(Sinh&&) = delete;
    Sinh& operator=(const Sinh&) = delete;
    Sinh& operator=(Sinh&&) = delete;

    double unaryOperation(double top) const override;

    Sinh* doClone() const override;
    string name() const override;

    //const char* helpMessageImpl() const noexcept override;
};

Sinh::Sinh(const Sinh& rhs)
    : HyperbolicLnPluginCommand{ rhs }
{ }

double Sinh::unaryOperation(double top) const
{
    return std::sinh(top);
}

Sinh* Sinh::doClone() const
{
    return new Sinh{ *this };
}

string Sinh::name() const {
    return "sinh";
}

//const char* Sinh::helpMessageImpl() const noexcept
//{
//    return "Replace the first element, x, on the stack with sinh(x)";
//}


void HyperbolicLnPlugin::createPluginDescriptor() {
    const int n = 1;
    pd_.nCommands = n;
    commandNames_.reserve(n);
    commands_.reserve(n);
    rawCommands_.resize(n);
    rawNames_.resize(n);
    commandNames_.emplace_back("sinh\0");
    commands_.emplace_back(new Sinh);
    for (int i = 0; i < n; i++) {
        rawCommands_[i] = commands_[i].get();
        rawNames_[i] = &commandNames_[i][0];
    }
    pd_.commands = &rawCommands_[0];
    pd_.commandNames = &rawNames_[0];
    return;
}