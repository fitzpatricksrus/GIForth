//
// Created by Dad on 9/16/19.
//

#include <utils/StringUtils.h>
#include <utils/NativeOSFunctions.hpp>
#include "words/PrimitiveForthWords.h"
#include "ForthThread.h"
#include "CompositeForthWord.h"
#include "utils/CompositeForthWordBuilder.h"

#include "utils/testing/debug.h"

/*
 * deadFrameWord is used for the "bottom of the return stack" and
 * causes the current thread to exit cleanly when interpreted
 */
static const CompositeForthWord deadFrameWord(
		CompositeForthWordBuilder("ForthThread::THREAD_ROOT_STUB")
			.compileCell(&PrimitiveForthWords::EXIT_THREAD)
		.build()
		);

static const ForthThread::ForthExecutionFrame THREAD_ROOT_STUB(ForthThread::ForthExecutionFrame(&deadFrameWord, 0));

ForthThread::ForthThread()
: dataStack(), returnStack(), ip(THREAD_ROOT_STUB), trace(false), traceDepth(0)
{
}

const CompositeForthWord* ForthThread::getCurrentWord() const {
    return ip.word;
}

void ForthThread::offsetIndex(int offset) {
    ip.ndx += offset;
	checkTrue(ip.ndx < ip.word->size());
}

const ForthCell &ForthThread::getCellAt(int ndx) const {
	checkTrue(ndx < ip.word->size());
    return (*ip.word)[ndx];
}

const ForthCell& ForthThread::getNextCell() {
	checkTrue(ip.ndx < ip.word->size());
    return (*ip.word)[ip.ndx++];
}

void ForthThread::pushFrame(const ForthExecutionFrame& frame) {
    toReturnStack(ip);
    ip = frame;
}

void ForthThread::popFrame() {
    ip = fromReturnStack().execution;
}

ForthCell ForthThread::peekDataStack(int ndx) const {
	checkTrue(ndx < dataStack.size());
    return (*this)[ndx];
}

void ForthThread::pokeDataStack(int ndx, const ForthCell& value) {
	checkTrue(ndx < dataStack.size());
    (*this)[ndx] = value;
}

void ForthThread::rollDataStack(int count) {
	checkTrue(count < dataStack.size());
#if 0
    // this is easier to read but less efficient (probably)
    ForthCell temp = (*this)[0];
    for (int i = count; i > 0; i--) {
        (*this)[i] = (*this)[i - 1];
    }
    (*this)[0] = temp;
#else
    const int size = dataStack.size();
    const int ndx = size - 1 - count;
    ForthCell temp = dataStack[ndx];
    dataStack.erase(dataStack.begin() + ndx, dataStack.begin() + ndx + 1);
    dataStack.push_back(temp);
#endif
}

ForthCell ForthThread::popDataStack() {
	checkTrue(!dataStack.empty());
    ForthCell result = dataStack.back();
    dataStack.pop_back();
    return result;
}

void ForthThread::pushDataStack(const ForthCell& value) {
    dataStack.push_back(value);
}

const ForthCell& ForthThread::operator[](int ndx) const {
	checkTrue(ndx < dataStack.size());
    return dataStack[dataStack.size() - 1 - ndx];
}

ForthCell& ForthThread::operator[](int ndx) {
	checkTrue(ndx < dataStack.size());
    return dataStack[dataStack.size() - 1 - ndx];
}

int ForthThread::getDataStackSize() const {
    return dataStack.size();
}

ForthThread::ReturnStackFrame ForthThread::fromReturnStack() {
	checkTrue(!returnStack.empty());
	ReturnStackFrame result = returnStack.top();
	returnStack.pop();
	return result;
}

const ForthThread::ReturnStackFrame &ForthThread::topOfReturnStack() const {
	checkTrue(!returnStack.empty());
    return returnStack.top();
}

void ForthThread::toReturnStack(const ReturnStackFrame& value) {
    returnStack.push(value);
}

int ForthThread::returnStackDepth() const {
    return returnStack.size();
}

void ForthThread::join() {
	PrimitiveForthWords::registers[PrimitiveForthWords::THREAD_STATE] = this;
	try {
		while (true) {
			checkTrue(ip.word);
			checkTrue(ip.ndx < ip.word->size());
			ForthWord *word = (*ip.word)[ip.ndx++].word;
			doTrace(word);
			try {
				word->execute(*this);
			} catch (const CheckException &e) {
				NativeOSFunctions::printString(e.msg);
				NativeOSFunctions::endLine();
			} catch (const std::exception &e) {
			}
		}
	} catch (const ThreadExitException &e) {
	}
	PrimitiveForthWords::registers[PrimitiveForthWords::THREAD_STATE] = static_cast<ForthCell::PTR_TYPE>(nullptr);
}

void ForthThread::join(const CompositeForthWord& word) {
	pushFrame(&word);
	join();
}

ForthThread* ForthThread::getCurrentThread() {
	return static_cast<ForthThread*>(PrimitiveForthWords::registers[PrimitiveForthWords::THREAD_STATE].pointer);
}

void ForthThread::enableTrace(bool enable) {
    trace = enable;
}

bool ForthThread::isTraceEnabled() const {
    return trace;
}

int ForthThread::getTraceDepth() const {
    return traceDepth;
}

void ForthThread::setTraceDepth(int depth) {
    traceDepth = depth;
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

void ForthThread::doTrace(const ForthWord* word) const {
	static constexpr int INDEX_TAB_POSITION = 52;
	static constexpr int FIRST_TAB_POSITION = 60;
	static constexpr int SECOND_TAB_POSITION = 120;

	if (!trace) return;

	std::string line;
	line += ip.word->getDisassemblyName();

	StringUtils::tabTo(line, INDEX_TAB_POSITION - 3);
	line += "[" ;
	StringUtils::rightTabTo(line, std::to_string(getIndex() - 1), INDEX_TAB_POSITION);
	line += " ] ";

	StringUtils::tabTo(line, FIRST_TAB_POSITION + getTraceDepth() * 2);
	line += word->getDisassemblyDetail(*this);

	StringUtils::tabTo(line, SECOND_TAB_POSITION);
	line += " ( ";
	line += shortStackDump(*this);
	line += " )";

	NativeOSFunctions::printString(line);
	NativeOSFunctions::endLine();
}

