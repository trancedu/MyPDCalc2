#include "CLI.h"
#include "stack.h"
#include "Tokenizer.h"
#include <sstream>

CLI::CLI(std::istream& in, std::ostream& out) : in_{ in }, out_{ out } {}

void CLI::showMessage(const string& message) {
    out_ << "Message: " << message << '\n';
}

void CLI::handleStackChanged() {
    out_ << "Stack: ";
    vector<double> data = Stack::Instance().getElements();
    for (const auto d : data) {
        out_ << d << '\t';
    }
    out_ << '\n';
}

void CLI::execute() {
    for (string line; std::getline(in_, line, '\n');) {
        std::istringstream iss{ line };
        Tokenizer tokenizer{ iss };
        for (const string& token : tokenizer) {
            if (token == "exit") return;
            raise(commandEnteredEventName(), token);
        }
    }
} 