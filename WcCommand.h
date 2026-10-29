#pragma once
#include "Command.h"

class WcCommand : public Command {
public:
	void configureCommand(const std::string& option, const std::vector<Token>& argument) override;
	void execute(std::istream& in, std::ostream& out) override;
	const Token* inputStreamArgument() const override; 
private:
	enum class Mode {WORDS, CHARACTERS};
	Mode mode = Mode::WORDS; 
	bool hasArgument = false;
	Token arg;
};

