#include "HeadCommand.h"
#include "Exceptions.h"

void HeadCommand::configureCommand(const std::string& option, const std::vector<Token>& argument) {
	if (argument.size() > 1) {
		throw SyntaxError("Head can have zero or one argument!");
	}
	if (option.size() >= 2 && option[0] == '-' && option[1] == 'n')  {
		std::string count = option.substr(2);
		if (count.empty()) {
			throw SyntaxError("Head needs at least one digit!");
		}
		if (count.size() > 5) {
			throw SyntaxError("Head needs max five digits!");
		}
		for (char c : count) {
			if(!std::isdigit(c)) throw SyntaxError("Head characters need to be digits!");
		}
		lineCount = std::stoi(count);
	}
	else {
		throw SyntaxError("Head: option is invalid, requires -ncount format!");
	}
	if (!argument.empty()) {
		hasArgument = true;
		arg = argument[0];
	}
}

void HeadCommand::execute(std::istream& in, std::ostream& out) {
	std::string lineText;
	for (int i = 0; i < lineCount && std::getline(in, lineText); i++) {
		out << lineText << "\n";
	}
	while (std::getline(in, lineText)) {
	}
}

const Token* HeadCommand::inputStreamArgument() const
{
	if (hasArgument) return &arg;
	return nullptr;
}
