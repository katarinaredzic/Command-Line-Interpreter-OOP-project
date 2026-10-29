#include "TrCommand.h"
#include "Exceptions.h"

void TrCommand::configureCommand(const std::string& option, const std::vector<Token>& argument) {
	std::vector<Token> all;
	if (!option.empty()) {
		all.push_back({ TokenType::WORD, option, 0 });
	}
	for (const auto& t : argument) {
		all.push_back(t);
	}

	std::size_t dashPos = all.size();
	for (std::size_t k = 0; k < all.size(); ++k) {
		if (all[k].type == TokenType::WORD && all[k].text == "-") {
			dashPos = k;
			break;
		}
	}

	if (dashPos == all.size()) {
		throw SyntaxError("TR: expected '-\"what\"' in the command!");
	}
	if (dashPos > 1) {
		throw SyntaxError("TR: too many tokens before '-what'!");
	}
	if (dashPos == 1) {
		hasArgument = true;
		arg = all[0];
	}

	std::size_t whatPos = dashPos + 1;
	if (whatPos >= all.size() || all[whatPos].type != TokenType::QUOTED_STRING) {
		throw SyntaxError("TR: 'what' must be a quoted string right after '-'!");
	}
	what = all[whatPos].text;
	if (what.empty()) {
		throw SyntaxError("TR: 'what' must not be empty!");
	}

	std::size_t withPos = whatPos + 1;
	if (withPos < all.size()) {
		if (all[withPos].type != TokenType::QUOTED_STRING) {
			throw SyntaxError("TR: 'with' must be a quoted string!");
		}
		with = all[withPos].text;
		if (withPos + 1 != all.size()) {
			throw SyntaxError("TR: too many arguments after 'with'!");
		}
	}
}

void TrCommand::execute(std::istream& in, std::ostream& out) {
	std::string text;
	std::string newText;
	char c;
	while (in.get(c)) {
		text += c;
	}
	std::size_t i = 0;
	std::size_t n = text.size();
	while (i < n) {
		if (text.compare(i, what.size(), what) == 0) {
			newText += with;
			i += what.size();
		}
		else {
			newText += text[i];
			i += 1;
		}
	}
	out << newText;
}

const Token* TrCommand::inputStreamArgument() const {
	if (hasArgument) return &arg;
	return nullptr;
}
