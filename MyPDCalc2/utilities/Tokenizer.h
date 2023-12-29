#pragma once
#include <sstream>
#include <string>
#include <vector>

class Tokenizer
{
public:
	Tokenizer(std::istringstream& iss) {
		tokenize(iss);
	}
	void tokenize(std::istringstream& iss) {
		std::string token;
		while (iss >> token) {
			tokens_.push_back(token);
		}
	}
	auto begin() { return tokens_.begin(); }
	auto end() { return tokens_.end(); }
private:
	std::vector<std::string> tokens_;
};

