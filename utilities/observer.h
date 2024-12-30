#pragma once
#include <any>
#include <string>
#include "export.h"

using std::string;

class UTILITIES_API Observer
{
public:
	virtual string name() const = 0;
	virtual void notify(const std::any& message) = 0;
	virtual ~Observer() = default;
};