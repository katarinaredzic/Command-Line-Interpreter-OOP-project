#include "Lexer.h"
#include <vector>
#include "Exceptions.h"

bool Lexer::isCharAllowed(char c) const {
	if (std::isalpha(c) || std::isdigit(c) || c == '-' || c == '.' || c == '_') {
		return true;
	}
	return false;
}

Lexer::Lexer(std::string line) {
	line_ = line;
}

std::vector<Token> Lexer::makeTokens() const {
	std::vector<Token> tokens;
	std::vector<std::size_t> signNotAllowed;
	std::size_t i = 0;
	std::size_t n = line_.size();

	while (i < n) {

		if (line_[i] == ' ' || line_[i] == '\t') {
			i++;
			continue;
		}
		if (isCharAllowed(line_[i])) {
			std::size_t wordStart = i;
			while (i < n && isCharAllowed(line_[i])) {
				i++;
			}
			std::size_t wordLength = i - wordStart;
			std::string word = line_.substr(wordStart, wordLength);
			tokens.push_back({ TokenType::WORD, word, wordStart });
			continue;
		}

		if (line_[i] == '|') {
			tokens.push_back({ TokenType::PIPE, "|" , i });
			i++;
			continue;
		}

		if (line_[i] == '<') {
			tokens.push_back({ TokenType::REDIRECT_IN, "<" , i });
			i++;
			continue;
		}

		if (line_[i] == '>') {
			std::size_t first = i;
			if (i + 1 < n && line_[i + 1] == '>') {
				tokens.push_back({ TokenType::REDIRECT_OUT_APPEND, ">>" , first });
				i += 2;
			}
			else {
				tokens.push_back({ TokenType::REDIRECT_OUT, ">" , first });
				i++;
			}
			continue;
		}

		if (line_[i] == '"') {
			std::size_t start = i;
			i++;
			std::size_t stringStart = i;

			while (i < n && line_[i] != '"') {
				i++;
			}
			if (i >= n) {
				signNotAllowed.push_back(start);
				continue;
			}
			std::size_t stringLength = i - stringStart;
			std::string content = line_.substr(stringStart, stringLength);
			tokens.push_back({ TokenType::QUOTED_STRING, content , start });
			i++;
			continue;
		}

		signNotAllowed.push_back(i);
		i++;
	}

	if (signNotAllowed.size() > 0) {
		throw LexicalError(line_, signNotAllowed);
	}

	tokens.push_back({ TokenType::END_FILE, " ", n });
	return tokens;
}
