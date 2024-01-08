#pragma once
#include <memory>
#include <string>
#include "stack.h"
#include "exception.h"
#include <math.h>

class Command
{
public:
	void execute() {
		checkPrecondition();
		executeImpl();
	}
	virtual std::string name() const = 0;
	virtual Command* clone() const = 0;
	virtual void undo() = 0;
	virtual void deallocate() { delete this; }
	virtual ~Command() = default;
private:
	virtual void checkPrecondition() const = 0;
	virtual void executeImpl() = 0;
};

inline void CommandDeleter(Command* p)
{
	if (p) p->deallocate();
	return;
}

using CommandPtr = unique_ptr<Command, decltype(&CommandDeleter)>;

template<typename T, typename... Args>
auto MakeCommandPtr(Args&&... args) requires std::derived_from<T, Command>
{
	return CommandPtr{ new T{std::forward<Args>(args)...}, &CommandDeleter };
}

inline auto MakeCommandPtr(Command* p)
{
	return CommandPtr{ p, &CommandDeleter };
}

class UnaryCommand : public Command
{
public:
	void checkPrecondition() const override {
		if (Stack::Instance().size() == 0) {
			throw Exception{ "There must be at least one element in Stack" };
		}
	}
	void executeImpl() override {
		prev_ = Stack::Instance().pop(false);
		double result = unaryOperation(prev_);
		Stack::Instance().push(result);
	}
	void undo() override {
		Stack::Instance().pop(false);
		Stack::Instance().push(prev_);
	}
private:
	virtual double unaryOperation(double num) const = 0;
	double prev_;
};


class Sine : public UnaryCommand
{
public:
	std::string name() const override { return "sin"; }
	double unaryOperation(double num) const override { return std::sin(num); }
	Command* clone() const override { return new Sine(*this); }
};


class BinaryCommand : public Command
{
public:
	void checkPrecondition() const override {
		if (Stack::Instance().size() < 2) {
			throw Exception{ "There must be at least two elements in Stack" };
		}
	}
	void executeImpl() override {
		second_ = Stack::Instance().pop(false);
		first_ = Stack::Instance().pop(false);
		double result = binaryOperation(first_, second_);
		Stack::Instance().push(result);
	}
	void undo() override {
		Stack::Instance().pop(false);
		Stack::Instance().push(first_);
		Stack::Instance().push(second_);
	}
private:
	double first_;
	double second_;
	virtual double binaryOperation(double num1, double num2) const = 0;
};

class Add : public BinaryCommand
{
public:
	std::string name() const override { return "+"; }
	double binaryOperation(double num1, double num2) const override { return num1 + num2; }
	Command* clone() const override { return new Add(*this); }
};

class EnterNumber : public Command
{
public:
	explicit EnterNumber(double num) : num_{ num } {}
	std::string name() const override { return "EnterNumber"; }
	void checkPrecondition() const override {}
	void executeImpl() override {
		Stack::Instance().push(num_);
	}
	void undo() override {
		Stack::Instance().pop();
	}
	Command* clone() const override { return new EnterNumber(*this); }
private:
	double num_;
};


class PluginCommand : public Command
{
public:
	virtual ~PluginCommand() = default;

private:
	virtual const char* checkPluginPreconditions() const noexcept = 0;
	virtual PluginCommand* clonePluginImpl() const noexcept = 0;

	void checkPrecondition() const override final;
	PluginCommand* clone() const override final;
};

void PluginCommand::checkPrecondition() const
{
	if (const char* p = checkPluginPreconditions())
		throw Exception(p);

	return;
}

PluginCommand* PluginCommand::clone() const
{
	if (auto p = clonePluginImpl())
		return p;
	else
		throw Exception("Problem cloning a plugin command");
}