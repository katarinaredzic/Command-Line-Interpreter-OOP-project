#pragma once
#include "Command.h"

class TouchCommand : public Command {
public:
	void configureCommand(const std::string& option, const std::vector<Token>& argument) override;
	void execute(std::istream& in, std::ostream& out) override;
	bool usingInputCharacterStream() const override { return false; }
	bool usingOutputCharacterStream() const override { return false; }
private:
	std::string fileName;
};

