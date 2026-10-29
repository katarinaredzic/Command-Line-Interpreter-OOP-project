#pragma once
#include <memory>
#include "Command.h"
#include "Redirection.h"
#include <vector>

class CommandInvocation {
public:
	CommandInvocation(std::unique_ptr<Command> command) : command(std::move(command)) {}

	void configureCommand(const std::string& option, const std::vector<Token>& argument) {
		command->configureCommand(option, argument);
	}

	void addRedirection(Redirection r) { redirections.push_back(std::move(r)); }

	void setPipelinePosition(bool hasPredecessor, bool hasSuccessor) {
		hasPipedInput = hasPredecessor;
		hasPipedOutput = hasSuccessor;
	}

	std::string execute(std::istream* pipedIn, std::ostream& consoleOut);

private:
	std::unique_ptr<Command> command;
	std::vector<Redirection> redirections;
	bool hasPipedInput = false;
	bool hasPipedOutput = false;
};

