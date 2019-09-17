//
// Created by Dad on 9/16/19.
//

#include "ForthThread.h"
#include "CompositeForthWord.h"

ForthThread::ForthThread(const ForthExecutionFrame& start)
: dataStack(), returnStack(), ip(start)
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
        return {nullptr};
    } else {
        ReturnStackFrame result = returnStack.top();
        returnStack.pop();
        return result;
    }
}

void ForthThread::toReturnStack(const ReturnStackFrame& value) {
    returnStack.push(value);
}

int ForthThread::returnStackDepth() const {
    return returnStack.size();
}

bool ForthThread::execute() {
    if (!ip.isDeadFrame()) {
        ip.word->execute(*this);
    }
    return !ip.isDeadFrame();
}

void ForthThread::join() {
    while (execute()) {};
}
