#include "BatchCommand.h"
#include "Exceptions.h"

void BatchCommand::configureCommand(const std::string& option, const std::vector<Token>& argument) {
	if (!option.empty()) {
		throw SyntaxError("Batch does not have options!");
	}
	if (argument.size() != 1 || argument[0].type != TokenType::WORD) {
		throw SyntaxError("Batch needs one argument (file name) type word!");
	}
	hasArgument = !argument.empty();
	if (hasArgument) {
		arg = argument[0];
	}
}

void BatchCommand::execute(std::istream& in, std::ostream& out) {
	std::string line;
	while (std::getline(in, line)) {
		executor_.executeLine(line, out);
	}
}
