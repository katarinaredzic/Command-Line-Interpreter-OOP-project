#pragma once
#include "Command.h"

class PromptCommand : public Command {
public:
	PromptCommand(IPromptSettable& sink) : sink_(sink){};
	void configureCommand(const std::string& option, const std::vector<Token>& argument) override;
	void execute(std::istream& in, std::ostream& out) override;
	virtual bool usingInputCharacterStream() const override { return false; }
	virtual bool usingOutputCharacterStream() const override { return false; }
private:
	IPromptSettable& sink_;
	std::string newPrompt_;
};

