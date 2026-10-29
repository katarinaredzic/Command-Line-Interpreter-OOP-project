#pragma once
#include "Command.h"

class BatchCommand : public Command {
public:
	explicit BatchCommand(ILineExecutor& executor): executor_(executor){} 
	void configureCommand(const std::string& option, const std::vector<Token>& argument) override;
	void execute(std::istream& in, std::ostream& out) override;
	const Token* inputStreamArgument() const override { return hasArgument ? &arg : nullptr; }
private:
	ILineExecutor& executor_;
	bool hasArgument = false;
	Token arg;
};

