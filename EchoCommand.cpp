#include "EchoCommand.h"
#include "Exceptions.h"

void EchoCommand::configureCommand(const std::string& option, const std::vector<Token>& argument) {
	if (!option.empty()) {
		throw SyntaxError("Echo does not have options!");
	}
	if (argument.size() > 1) {
		throw SyntaxError("Echo can have zero or one argument!");
	}
	if (!argument.empty()) {
		hasArgument = true;
		arg = argument[0];
	}
}

void EchoCommand::execute(std::istream& in, std::ostream& out) {
	out << in.rdbuf();
}

const Token* EchoCommand::inputStreamArgument() const {
	if (hasArgument) return &arg;
	return nullptr;
}
