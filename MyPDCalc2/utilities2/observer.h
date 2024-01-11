#pragma once
#include <any>
#include <string>
using std::string;

class Observer
{
public:
	virtual string name() const = 0;
	virtual void notify(const std::any& message) = 0;
};