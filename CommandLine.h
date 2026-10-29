#pragma once
#include <vector>
#include "CommandInvocation.h"

class CommandLine {
public:
	void addSequence(std::unique_ptr<CommandInvocation> sequence) { sequence_.push_back(std::move(sequence)); }
	void execute(std::ostream& out);

private:
	std::vector<std::unique_ptr<CommandInvocation>> sequence_;
};

