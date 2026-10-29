#include "WcCommand.h"
#include "Exceptions.h"

void WcCommand::configureCommand(const std::string& option, const std::vector<Token>& argument) {
	if (option == "-w") {
		mode = Mode::WORDS;
	} else if (option == "-c") {
		mode = Mode::CHARACTERS;
	} else {
		throw SyntaxError("WC needs options: -w or -c!");
	}
	
	if (argument.size() > 1) {
		throw SyntaxError("WC can have zero or one argument!");
	}
	if (!argument.empty()) { 
		hasArgument = true;
		arg = argument[0];
	}
}

void WcCommand::execute(std::istream& in, std::ostream& out) {
	int count = 0;
	bool inWord = false;
	if (mode == Mode::CHARACTERS) {
		char c;
		while (in.get(c)) {
			count++;
		}
	}
	if (mode == Mode::WORDS){
		char c;
		while (in.get(c)) {
			if (std::isspace(c)) {
				inWord = false;
			}
			else if (!inWord) {
				inWord = true;
				count++;
			}
		}
	}
	out << count << std::endl;
}

const Token* WcCommand::inputStreamArgument() const {
	if (hasArgument) return &arg;
	return nullptr;
}
