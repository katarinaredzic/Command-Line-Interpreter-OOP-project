#pragma once
#include <iostream>
#include <string>
#include "Lexer.h"
#include "Parser.h"
#include "CommandFactory.h"
#include "Command.h"

class Interpreter : public IPromptSettable, public ILineExecutor {
public:
	Interpreter();
	void run(std::istream& in, std::ostream& out);
	void setPrompt(const std::string& newPrompt) override { prompt = newPrompt + " "; }
	void executeLine(const std::string& line, std::ostream& out) override;

private:
	static const std::size_t maxLineLength = 512;
	std::string prompt = "$ ";
	std::ostream* errorOut_ = nullptr;
	CommandFactory makeCommand_;
	Parser parser_;

	std::string readLine(std::istream& in) const;
	

};

