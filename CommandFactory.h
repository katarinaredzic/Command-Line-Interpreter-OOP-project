#pragma once
#include "Command.h"
#include <memory>

class CommandFactory {
public:
	CommandFactory(IPromptSettable& promptSink, ILineExecutor& lineExecutor);
	std::unique_ptr<Command> create(const std::string& commandName) const;
private:
	IPromptSettable& promptSink_;
	ILineExecutor& lineExecutor_;;
};

