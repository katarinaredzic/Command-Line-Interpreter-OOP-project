#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Token.h"

class Command {
public:
	virtual ~Command() = default;
	virtual void configureCommand(const std::string& option, const std::vector<Token>& argument) = 0;
	virtual void execute(std::istream& in, std::ostream& out) = 0;
	virtual bool usingInputCharacterStream() const { return true; }
	virtual bool usingOutputCharacterStream() const { return true; }
	virtual const Token* inputStreamArgument() const { return nullptr; }
};

class IPromptSettable {
public:
	virtual ~IPromptSettable() = default;
	virtual void setPrompt(const std::string& newPrompt) = 0;
};

class ILineExecutor {
public:
	virtual ~ILineExecutor() = default;
	virtual void executeLine(const std::string& line, std::ostream& out) = 0;
};