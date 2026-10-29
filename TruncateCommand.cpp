#include "TruncateCommand.h"
#include "Exceptions.h"
#include <fstream>
#include <filesystem>


void TruncateCommand::configureCommand(const std::string& option, const std::vector<Token>& argument){
	if (!option.empty()) {
		throw SyntaxError("Truncate does not have options!");
	}
	if (argument.size() != 1 || argument[0].type != TokenType::WORD) {
		throw SyntaxError("Truncate accepts only one argument (type WORD)!");
	}
	fileName = argument[0].text;
}

void TruncateCommand::execute(std::istream& in, std::ostream& out) {
	namespace fs = std::filesystem;
	if (!fs::exists(fileName)) {
		throw CommandExecutionError("File with the name: " + fileName + " does not exist!");
	}
	if (fs::is_empty(fileName)) {
		throw CommandExecutionError("File is already empty!");
	}
	std::ofstream file(fileName, std::ios::trunc);
	if (!file.is_open()) {
		throw CommandExecutionError("Error opening file!");
	}
}
