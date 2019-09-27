//
// Created by Dad on 9/16/19.
//

#include "CompositeForthWord.h"
#include "ForthThread.h"
#include "utils/NativeOSFunctions.hpp"


#undef OPTIMIZE_DISPATCH

bool CompositeForthWord::trace = false;

void CompositeForthWord::enableTrace(bool enable) {
    trace = enable;
}

bool CompositeForthWord::isTraceEnabled() {
    return trace;
}

#ifndef OPTIMIZE_DISPATCH

void CompositeForthWord::execute(ForthThread& thread) {
    if (thread.getCurrentWord() != this) {
        // first time called, so make a new stack frame
        thread.pushFrame(this);
    }
    int ndx = thread.getIndex();
    if (ndx < body.size()) {
        ForthWord* word = body[ndx].word;
        thread.setIndex(ndx + 1);
        if (isTraceEnabled()) {
            NativeOSFunctions::printString(word->getDisassembly(thread));
            NativeOSFunctions::printChar('\n');
        }
        word->execute(thread);
    } else {
        thread.popFrame();
    }
}

#else

void CompositeForthWord::execute(ForthThread& thread) {
    if (thread.getCurrentWord() != this) {
        // first time called, so make a new stack frame
        thread.pushFrame(this);
    }
    int ndx = thread.getIndex();
    if (ndx < body.size()) {
        ForthWord* word = body[ndx].word;
        thread.setIndex(ndx + 1);
        word->execute(thread);
    } else {
        thread.popFrame();
    }
}




#endif

std::string CompositeForthWord::doDisassembly(const ForthThread& thread) const {
    return name;
}

int CompositeForthWord::getDisassemblyParamCount() const {
    return 0;
}

