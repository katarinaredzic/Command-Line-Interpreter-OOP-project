#pragma once
#include "Token.h"
#include "CommandFactory.h"
#include "CommandLine.h"
#include <vector>

class Parser {
public:
	Parser(const CommandFactory& makeCommand) : makeCommand(makeCommand) {}
	std::unique_ptr<CommandLine> parse(const std::vector<Token>& tokens);

private:
	const CommandFactory& makeCommand;
};

