#include "Interpreter.h"
#include "Exceptions.h"

Interpreter::Interpreter() : makeCommand_(*this, *this), parser_(makeCommand_){}

void Interpreter::run(std::istream& in, std::ostream& out) {
	errorOut_ = &out;
	while (in) {
		in.clear();
		out << std::endl << prompt;
		std::string line = readLine(in);
		if (!in && line.empty()) {
			break;
		}
		executeLine(line, out);
	}
}

std::string Interpreter::readLine(std::istream& in) const {
	std::string line;
	std::getline(in, line);
	if (line.size() > maxLineLength) {
		line.resize(maxLineLength);
	}
	return line;
}

void Interpreter::executeLine(const std::string& line, std::ostream& out) {
	try {
		Lexer lexer(line);
		auto tokens = lexer.makeTokens();
		auto commandLine = parser_.parse(tokens);
		commandLine->execute(out);
	}
	catch (const LexicalError& e) {
		*errorOut_ << e.what() << "\n" << e.get_line() << "\n";
		std::string marker;
		std::size_t lineLenght = e.get_line().size();
		const auto& badPosition = e.get_signNotAllowed();

		for (std::size_t currPos = 0; currPos < lineLenght; currPos++) {
			bool isBad = false;
			for (auto badPos : badPosition) {
				if (badPos == currPos) {
					isBad = true;
					break;
				}
			}
			marker += isBad ? '^' : ' ';
		}
		*errorOut_ << marker << "\n";
	}
	catch (const InterpreterError& e) {
		*errorOut_ << "Error: " << e.what() << "\n";
	}
}


	