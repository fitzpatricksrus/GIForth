#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-pass-by-value"

#include "utils/StringUtils.h"
#include "CompositeForthWord.h"
#include "ForthThread.h"

CompositeForthWord::CompositeForthWord(const std::string &nameIn, const std::vector<ForthCell>& cellsIn)
		: body(cellsIn), name(nameIn)
{
}

void CompositeForthWord::execute(ForthThread& thread) const {
	thread.pushFrame(this);
	thread.setTraceDepth(thread.getTraceDepth() + 1);
}

std::string CompositeForthWord::getDisassemblyName() const {
	return name;
}

std::string CompositeForthWord::getDisassemblyDetail(const ForthThread& thread) const {
	return name;
}
