#pragma once
#include <string>
#include <string_view>
using std::string, std::string_view;

class Exception
{
public:
	explicit Exception(string_view message) : message_{ message } {}
	const char* what() const { return message_.c_str(); }
private:
	string message_;
};