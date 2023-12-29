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
	virtual Command* clone() = 0;
	virtual void undo() = 0;
private:
	virtual void checkPrecondition() const = 0;
	virtual void executeImpl() = 0;
};


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
	Command* clone() override { return new Sine(*this); }
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
	Command* clone() override { return new Add(*this); }
};