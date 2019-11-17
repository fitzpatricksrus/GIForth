#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-pass-by-value"
//
// Created by Dad on 9/16/19.
//

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

CompositeForthWord::CompositeForthWord(const std::string &nameIn, std::shared_ptr<const std::vector<ForthCell>> cellsIn)
		: body(cellsIn), name(nameIn)
{
}


CompositeForthWord::CompositeForthWord(const CompositeForthWord &other)
		: body(other.body), name(other.name) {

}

static std::string shortStackDump(const ForthThread& thread) {
	std::string line;
	int stackSize = thread.getDataStackSize();
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
	if (thread.getCurrentWord() != this) {
		// first time called, so make a new stack frame
		thread.pushFrame(this);
		thread.setTraceDepth(thread.getTraceDepth() + 1);
	}
	int ndx = thread.getIndex();
	ForthWord *word = (*body)[ndx].word;
	thread.setIndex(ndx + 1);
	trace(thread, word);
	word->execute(thread);
}

std::vector<std::string> CompositeForthWord::getDisassembly() const {
	std::vector<std::string> result(size());
	ForthThread disassemblyThread(const_cast<CompositeForthWord*>(this));
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
