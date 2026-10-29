#include "Parser.h"
#include "Exceptions.h"
#include "Redirection.h"
#include "CommandLine.h"

std::unique_ptr<CommandLine> Parser::parse(const std::vector<Token>& tokens) {
    auto line = std::make_unique<CommandLine>();
    std::size_t i = 0;
    std::size_t n = tokens.size();
    
    while (i < n && tokens[i].type != TokenType::END_FILE) {
        if (i >= n || tokens[i].type != TokenType::WORD) {
            throw SyntaxError("expected a command name!");
        }
        std::string commandName = tokens[i].text;
        i++;

        std::unique_ptr<Command> command = makeCommand.create(commandName);

        std::string option;
        if (i < n && tokens[i].type == TokenType::WORD && !tokens[i].text.empty() && tokens[i].text[0] == '-') {
            option = tokens[i].text;
            i++;
        }

        std::vector<Token> argument;
        while (i < n && (tokens[i].type == TokenType::QUOTED_STRING || tokens[i].type == TokenType::WORD)) {
            argument.push_back(tokens[i]);
            i++;
        }

        command->configureCommand(option, argument);
        auto invocation = std::make_unique<CommandInvocation>(std::move(command));
      
        while (i < n && (tokens[i].type == TokenType::REDIRECT_IN ||
            tokens[i].type == TokenType::REDIRECT_OUT ||
            tokens[i].type == TokenType::REDIRECT_OUT_APPEND)) {

            RedirectionType redirType;
            if (tokens[i].type == TokenType::REDIRECT_IN) {
                redirType = RedirectionType::INPUT;
            }
            else if (tokens[i].type == TokenType::REDIRECT_OUT) {
                redirType = RedirectionType::OUTPUT;
            }
            else if (tokens[i].type == TokenType::REDIRECT_OUT_APPEND) {
                redirType = RedirectionType::OUTPUT_APPEND;
            }
            i++;

            if (i >= n || tokens[i].type != TokenType::WORD) {
                throw SyntaxError("expected a filename after a redirection symbol");
            }

            invocation->addRedirection({ redirType, tokens[i].text });
            i++;
        }

        line->addSequence(std::move(invocation));

        if (i < n && tokens[i].type == TokenType::PIPE) {
            i++;
            continue;
        }
        if (i >= n || tokens[i].type != TokenType::END_FILE) {
            throw SyntaxError("Unexpected token in command line, should be the end");
        }
    }
    return line;
}
