#pragma once
#include <vector>
#include "Token.h"

class Lexer {
public:
	Lexer(std::string line);
	std::vector<Token> makeTokens() const;

private:
	bool isCharAllowed(char c) const;
	std::string line_;
};

