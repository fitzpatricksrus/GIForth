//
// Created by Dad on 9/16/19.
//

#include "ForthThread.h"
#include "CompositeForthWord.h"

const ForthThread::ReturnStackFrame ForthThread::DEAD_FRAME(ForthExecutionFrame(nullptr));

ForthThread::ForthThread(const ForthExecutionFrame& start)
: dataStack(), returnStack(), ip(start), trace(false), traceDepth(0)
{
}


CompositeForthWord* ForthThread::getCurrentWord() const {
    return ip.word;
}

int ForthThread::getIndex() const {
    return ip.ndx;
}

void ForthThread::setIndex(int newIndex) {
    ip.ndx = newIndex;
}

void ForthThread::offsetIndex(int offset) {
    ip.ndx += offset;
}

const ForthCell &ForthThread::getCellAt(int ndx) const {
    return (*ip.word)[ip.ndx];
}

const ForthCell& ForthThread::getNextCell() {
    return (*ip.word)[ip.ndx++];
}

bool ForthThread::currentWordComplete() const {
    return ip.ndx >= (*ip.word).size();
}

void ForthThread::pushFrame(CompositeForthWord* word, int ndx) {
    toReturnStack(ip);
    ip = ForthExecutionFrame(word, ndx);
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
    if (returnStack.empty()) {
        // this will return a frame with a nullptr word which will cause the thread to exit/join
        return DEAD_FRAME;
    } else {
        ReturnStackFrame result = returnStack.top();
        returnStack.pop();
        return result;
    }
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

bool ForthThread::execute() {
	currentThread = this;
    ip.word->execute(*this);
    currentThread = nullptr;
    return !ip.isDeadFrame();
}

void ForthThread::join() {
    if (!ip.isDeadFrame()) {
        while (execute()) {};
    }
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

