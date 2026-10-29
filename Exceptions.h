#pragma once
#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>

class InterpreterError: public std::runtime_error {
public:
	InterpreterError(std::string message) : std::runtime_error(message) {};
};

class LexicalError : public InterpreterError {
public:
	explicit LexicalError(std::string line, std::vector<std::size_t> signNotAllowed)
		: InterpreterError("Error - unexpected characters: ") {
		line_ = line;
		signNotAllowed_ = signNotAllowed;
	}
	const std::string& get_line() const { return line_; }
	const std::vector<std::size_t>& get_signNotAllowed() const { return signNotAllowed_; }

private:
	std::string line_;
	std::vector<std::size_t> signNotAllowed_;
};

class UnknownCommandError : public InterpreterError {
public:
	explicit UnknownCommandError(std::string command) : InterpreterError("Unknown command: " + command) {
		command_ = command;
	}
	const std::string& get_command() const { return command_; }

private:
	std::string command_;
};

class SyntaxError : public InterpreterError {
public:
	explicit SyntaxError(std::string message) : InterpreterError("Syntax error: " + message) {}
};

class SemanticError : public InterpreterError {
public:
	explicit SemanticError(std::string message) : InterpreterError("Semantic error: " + message) {}
};

class SystemError : public InterpreterError {
public:
	explicit SystemError(std::string message) : InterpreterError(message) {}
};

class CommandExecutionError : public InterpreterError {
public:
	explicit CommandExecutionError(std::string message) : InterpreterError(message) {}
};