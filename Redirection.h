#pragma once
#include <string>

enum class RedirectionType{
	INPUT,
	OUTPUT,
	OUTPUT_APPEND
};

struct Redirection {
	RedirectionType redirType;
	std::string fileName;
};