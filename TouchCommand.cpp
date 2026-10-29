#include "TouchCommand.h"
#include "Exceptions.h"
#include <fstream>
#include <filesystem>

void TouchCommand::configureCommand(const std::string& option, const std::vector<Token>& argument) {
	if (!option.empty()) {
		throw SyntaxError("Touch does not have options!");
	}
	if (argument.size() != 1 || argument[0].type != TokenType::WORD) {
		throw SyntaxError("Touch accepts only one argument (type WORD)!");
	}
	fileName = argument[0].text;
}

void TouchCommand::execute(std::istream&, std::ostream&) {
	namespace fs = std::filesystem;
	if (fs::exists(fileName)) {
		throw CommandExecutionError("File with the name: " + fileName + " already exists!");
	}
	std::ofstream file(fileName);
	if (!file.is_open()) {
		throw CommandExecutionError("Error creating file!");
	}
}
