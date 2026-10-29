#pragma once
#include "Command.h"
class HeadCommand : public Command {
public:
	void configureCommand(const std::string& option, const std::vector<Token>& argument) override;
	void execute(std::istream& in, std::ostream& out) override;
	const Token* inputStreamArgument() const override;
private:
	bool hasArgument = false;
	Token arg;
	int lineCount = 0;
};

