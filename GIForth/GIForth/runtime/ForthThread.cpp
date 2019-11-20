//
// Created by Dad on 9/16/19.
//

#include "words/PrimitiveForthWords.h"
#include "ForthThread.h"
#include "CompositeForthWord.h"
#include "utils/CompositeForthWordBuilder.h"

/*
 * deadFrameWord is used for the "bottom of the return stack" and
 * causes the current thread to exit cleanly when interpreted
 */
static const CompositeForthWord deadFrameWord(
		CompositeForthWordBuilder("ForthThread::DEAD_FRAME")
			.compileCell(&PrimitiveForthWords::EXIT_THREAD)
		.build()
		);

const ForthThread::ForthExecutionFrame ForthThread::DEAD_FRAME(ForthExecutionFrame(&deadFrameWord, 0));

ForthThread::ForthThread()
		: dataStack(), returnStack(), ip(DEAD_FRAME), trace(false), traceDepth(0)
{
}

const CompositeForthWord* ForthThread::getCurrentWord() const {
    return ip.word;
}

void ForthThread::offsetIndex(int offset) {
    ip.ndx += offset;
}

const ForthCell &ForthThread::getCellAt(int ndx) const {
    return (*ip.word)[ndx];
}

const ForthCell& ForthThread::getNextCell() {
    return (*ip.word)[ip.ndx++];
}

bool ForthThread::currentWordComplete() const {
    return ip.ndx >= (*ip.word).size();
}

void ForthThread::pushFrame(const ForthExecutionFrame& frame) {
    toReturnStack(ip);
    ip = frame;
}

void ForthThread::popFrame() {
    ip = fromReturnStack().execution;
}

ForthCell ForthThread::peekDataStack(int ndx) const {
    return (*this)[ndx];
}

void ForthThread::pokeDataStack(int ndx, const ForthCell& value) {
    (*this)[ndx] = value;
}

void ForthThread::rollDataStack(int count) {
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
    ForthCell result = dataStack.back();
    dataStack.pop_back();
    return result;
}

void ForthThread::pushDataStack(const ForthCell& value) {
    dataStack.push_back(value);
}

const ForthCell& ForthThread::operator[](int ndx) const {
    return dataStack[dataStack.size() - 1 - ndx];
}

ForthCell& ForthThread::operator[](int ndx) {
    return dataStack[dataStack.size() - 1 - ndx];
}

int ForthThread::getDataStackSize() const {
    return dataStack.size();
}

ForthThread::ReturnStackFrame ForthThread::fromReturnStack() {
	ReturnStackFrame result = returnStack.top();
	returnStack.pop();
	return result;
}

const ForthThread::ReturnStackFrame &ForthThread::topOfReturnStack() const {
    return returnStack.top();
}

void ForthThread::toReturnStack(const ReturnStackFrame& value) {
    returnStack.push(value);
}

int ForthThread::returnStackDepth() const {
    return returnStack.size();
}

void ForthThread::join() {
	currentThread = this;
	try {
		while (true) {
			ip.word->execute(*this);
		}
	} catch (const ThreadExitException& e) {
	}
	currentThread = nullptr;
}

void ForthThread::join(const CompositeForthWord& word) {
	// force top frame to be the ContinuingForthWord for
	// word.  Otherwise we just keep pushing stack frames.
	// see CompositeForthWord.execute implementation
	word.execute(*this);
	join();
}

const ForthThread* ForthThread::getCurrentThread() {
	return currentThread;
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

thread_local ForthThread* ForthThread::currentThread = nullptr;

