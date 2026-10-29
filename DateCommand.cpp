#include "DateCommand.h"
#include "Exceptions.h"
#include <iostream>
#include <iomanip>
#include <ctime>

void DateCommand::configureCommand(const std::string& option, const std::vector<Token>& argument) {
	if (!option.empty() || !argument.empty()) {
		throw SyntaxError("Date does not have option or argument!");
	}
}

void DateCommand::execute(std::istream& in, std::ostream& out) {
	std::time_t t = std::time(nullptr);
	std::tm tmValue = {};
	localtime_s(&tmValue, &t);
	out << std::put_time(&tmValue, "%d.%m.%Y.") << "\n";
}
