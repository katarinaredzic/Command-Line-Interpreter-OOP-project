#include "CommandFactory.h"
#include "Exceptions.h"

#include "EchoCommand.h"
#include "TouchCommand.h"
#include "WcCommand.h"
#include "TrCommand.h"
#include "TruncateCommand.h"
#include "TimeCommand.h"
#include "DateCommand.h"
#include "RmCommand.h"
#include "HeadCommand.h"
#include "PromptCommand.h"
#include "BatchCommand.h"

CommandFactory::CommandFactory(IPromptSettable& promptSink, ILineExecutor& lineExecutor)
	: promptSink_(promptSink), lineExecutor_(lineExecutor) {}

std::unique_ptr<Command> CommandFactory::create(const std::string& commandName) const {

	if (commandName == "echo") return std::make_unique<EchoCommand>();
	if (commandName == "touch") return std::make_unique<TouchCommand>();
	if (commandName == "wc") return std::make_unique<WcCommand>();
	if (commandName == "time") return std::make_unique<TimeCommand>();
	if (commandName == "date") return std::make_unique<DateCommand>();
	if (commandName == "rm") return std::make_unique<RmCommand>();
	if (commandName == "tr") return std::make_unique<TrCommand>();
	if (commandName == "truncate") return std::make_unique<TruncateCommand>();
	if (commandName == "head") return std::make_unique<HeadCommand>();
	if (commandName == "prompt") return std::make_unique<PromptCommand>(promptSink_);
	if (commandName == "batch") return std::make_unique<BatchCommand>(lineExecutor_);

	throw UnknownCommandError(commandName);
}
