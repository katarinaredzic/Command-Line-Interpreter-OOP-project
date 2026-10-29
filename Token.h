#pragma once
#include <iostream>

enum class TokenType {
	WORD,
	QUOTED_STRING,
	REDIRECT_IN,
	REDIRECT_OUT,
	REDIRECT_OUT_APPEND,
	PIPE,
	END_FILE,

};

struct Token {
	TokenType type;
	std::string text;
	std::size_t position; 
};