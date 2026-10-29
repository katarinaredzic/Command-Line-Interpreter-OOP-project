#include "CommandInvocation.h"
#include "Exceptions.h"
#include "Redirection.h"
#include <sstream>
#include <fstream>

std::string CommandInvocation::execute(std::istream* pipedIn, std::ostream& consoleOut) {

	const Redirection* inRedir = nullptr;
	for (const auto& r : redirections) {
		if (r.redirType == RedirectionType::INPUT) {
			inRedir = &r;
			break;
		}
	}
	const Redirection* outRedir = nullptr;
	for (const auto& r : redirections) {
		if (r.redirType == RedirectionType::OUTPUT) {
			outRedir = &r;
			break;
		}
	}

	const Redirection* outAppRedir = nullptr;
	for (const auto& r : redirections) {
		if (r.redirType == RedirectionType::OUTPUT_APPEND) {
			outAppRedir = &r;
			break;
		}
	}

	if (command->inputStreamArgument() && inRedir) {
		throw SemanticError("command cannot have both an argument and input redirection");
	}
	if (command->inputStreamArgument() && hasPipedInput) {
		throw SemanticError("command's input is piped and cannot also have an argument");
	}
	if (hasPipedInput && !command->usingInputCharacterStream()) {
		throw SemanticError("command without an input stream can only be first in a pipeline");
	}
	if (hasPipedOutput && !command->usingOutputCharacterStream()) {
		throw SemanticError("command without an output stream can only be last in a pipeline");
	}
	if (inRedir && hasPipedInput) {
		throw SemanticError("command's input is piped and cannot also be redirected");
	}
	if ((outRedir || outAppRedir) && hasPipedOutput) {
		throw SemanticError("command's output is piped and cannot also be redirected");
	}
	if (outRedir && outAppRedir) {
		throw SemanticError("command cannot redirect its output to a file twice");
	}
	

	std::istringstream pipedInStream;
	std::istream* in = &std::cin;
	std::ifstream fileIn;
	if (command->usingInputCharacterStream()) {
		const Token* inlineArgument = command->inputStreamArgument();
		if (inlineArgument) {
			if (inlineArgument->type == TokenType::QUOTED_STRING) {
				pipedInStream.str(inlineArgument->text);
				in = &pipedInStream;  
			}
			if (inlineArgument->type == TokenType::WORD) {
				fileIn.open(inlineArgument->text);
				if (!fileIn) {
					throw CommandExecutionError("Could not open input file: " + inlineArgument->text);
				}
				in = &fileIn;
			}
		}
		else if (inRedir) {
			fileIn.open(inRedir->fileName);
			if (!fileIn) {
				throw CommandExecutionError("Could not open input file: " + inRedir->fileName);
			}
			in = &fileIn;
		}
		else if (hasPipedInput && pipedIn) {
			in = pipedIn;
		}
		else in = &std::cin;
	}

	std::ostringstream pipedOut;
	std::ostream* out = &consoleOut;
	std::ofstream fileOut;

	if (command->usingOutputCharacterStream()) {
		if (outRedir) {
			fileOut.open(outRedir->fileName, std::ios::trunc);
			if (!fileOut) {
				throw CommandExecutionError("Could not open output file: " + outRedir->fileName);
			}
			out = &fileOut;
		}
		else if (outAppRedir) {
			fileOut.open(outAppRedir->fileName, std::ios::app);
			if (!fileOut) {
				throw CommandExecutionError("Could not open output file: " + outAppRedir->fileName);
			}
			out = &fileOut;
		}
		else if (hasPipedOutput) {
			out = &pipedOut; //output ide ili na pipe ili na konzolu
		}
		else out = &consoleOut;
	}
	command->execute(*in, *out);
	if (hasPipedOutput) {
		return pipedOut.str();
	}
	else return std::string();

}
