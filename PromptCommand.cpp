#include "PromptCommand.h"
#include "Exceptions.h"

void PromptCommand::configureCommand(const std::string& option, const std::vector<Token>& argument) {
	if (!option.empty()) {
		throw SyntaxError("Prompt does not have options!");
	}
	if (argument.size() != 1 || argument[0].type != TokenType::QUOTED_STRING) {
		throw SyntaxError("Prompt needs one argument type QUOTED-STRING!");
	}
	newPrompt_ = argument[0].text;
}

void PromptCommand::execute(std::istream& in, std::ostream& out) {
	sink_.setPrompt(newPrompt_);
}
