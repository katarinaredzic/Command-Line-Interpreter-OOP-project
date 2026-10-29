#include "RmCommand.h"
#include "Exceptions.h"
#include <filesystem>

void RmCommand::configureCommand(const std::string& option, const std::vector<Token>& argument) {
	if (!option.empty()) {
		throw SyntaxError("RM does not have options!");
	}
	if (argument.size() != 1 || argument[0].type != TokenType::WORD) {
		throw SyntaxError("RM accepts only one argument (type WORD)!");
	}
	fileName = argument[0].text;
}

void RmCommand::execute(std::istream& in, std::ostream& out) {
	namespace fs = std::filesystem;
	if (!fs::exists(fileName)) {
		throw CommandExecutionError("File with the name: " + fileName + " does not exist!");
	}
	std::error_code ec;
	fs::remove(fileName, ec);
	if (ec) {
		throw CommandExecutionError("Error deleting/removing file!");
	}
}
