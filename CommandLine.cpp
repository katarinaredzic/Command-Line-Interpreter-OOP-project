#include "CommandLine.h"
#include <sstream>

void CommandLine::execute(std::ostream& out) {
	std::string carried;
	std::istringstream carriedStream;

	for (std::size_t i = 0; i < sequence_.size(); i++) {
		bool hasPredecessor = i > 0;
		bool hasSuccessor = i + 1 < sequence_.size();
		sequence_[i]->setPipelinePosition(hasPredecessor, hasSuccessor);

		std::istream* pipedIn = nullptr;
		if (hasPredecessor) {
			carriedStream.clear();
			carriedStream.str(carried);
			pipedIn = &carriedStream;
		}
		carried = sequence_[i]->execute(pipedIn, out);
	}

}
