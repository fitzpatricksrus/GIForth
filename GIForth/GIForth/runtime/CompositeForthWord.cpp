#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-pass-by-value"

#include "utils/StringUtils.h"
#include "CompositeForthWord.h"
#include "ForthThread.h"
#include "utils/NativeOSFunctions.hpp"

CompositeForthWord::CompositeForthWord(const std::string &nameIn, const std::vector<ForthCell>& cellsIn)
		: body(), name(nameIn)
{
	auto ptr = new std::vector<ForthCell>(cellsIn);
	body = std::shared_ptr<const std::vector<ForthCell>>(ptr);
}

CompositeForthWord::CompositeForthWord(const std::string &nameIn, const std::shared_ptr<const std::vector<ForthCell>>& cellsIn)
		: body(cellsIn), name(nameIn)
{
}

static std::string shortStackDump(const ForthThread& thread) {
	std::string line;
	int stackSize = thread.getDataStackSize();
	if (stackSize >= 4) {
		line += "... ";
	}
	if (stackSize >= 3) {
		line += std::to_string(thread[2].integer);
		line += " ";
	}
	if (stackSize >= 2) {
		line += std::to_string(thread[1].integer);
		line += " ";
	}
	if (stackSize >= 1) {
		line += std::to_string(thread[0].integer);
	}
	return line;
}

void CompositeForthWord::execute(ForthThread& thread) const {
	thread.pushFrame(this);
	thread.setTraceDepth(thread.getTraceDepth() + 1);
}

std::vector<std::string> CompositeForthWord::getDisassembly() const {
	std::vector<std::string> result(size());
	ForthThread disassemblyThread;
	disassemblyThread.pushFrame(const_cast<CompositeForthWord*>(this));
	while (!disassemblyThread.currentWordComplete()) {
		ForthCell cell = disassemblyThread.getNextCell();
		std::string line(cell.word->getTrace(disassemblyThread));
		result.push_back(line);
		disassemblyThread.offsetIndex(cell.word->getDisassemblyParamCount());
	}
	return result;
}

void CompositeForthWord::trace(const ForthThread& thread, ForthWord* word) const {
	static constexpr int FIRST_TAB_POSITION = 40;
	static constexpr int SECOND_TAB_POSITION = 80;

	if (thread.isTraceEnabled()) {
		std::string line(getDisassemblyName());
		StringUtils::tabTo(line, FIRST_TAB_POSITION);
		line += " ( ";
		line += shortStackDump(thread);
		line += " )";
		StringUtils::tabTo(line, SECOND_TAB_POSITION + thread.getTraceDepth() * 2);
		line += word->getTrace(thread);
		NativeOSFunctions::printString(line);
		NativeOSFunctions::endLine();
	}
}

std::string CompositeForthWord::getDisassemblyName() const {
	return name;
}

std::string CompositeForthWord::getDisassemblyDetail(const ForthThread& thread) const {
	return name;
}

int CompositeForthWord::getDisassemblyParamCount() const {
	return 0;
}
