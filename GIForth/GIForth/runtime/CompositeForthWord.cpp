//
// Created by Dad on 9/16/19.
//

#include "utils/StringUtils.h"
#include "CompositeForthWord.h"
#include "ForthThread.h"
#include "utils/NativeOSFunctions.hpp"


#undef OPTIMIZE_DISPATCH

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

#ifndef OPTIMIZE_DISPATCH

void CompositeForthWord::execute(ForthThread& thread) {
	if (thread.getCurrentWord() != this) {
        // first time called, so make a new stack frame
        thread.pushFrame(this);
        thread.setTraceDepth(thread.getTraceDepth() + 1);
    }
    int ndx = thread.getIndex();
//    if (ndx < body.size()) {
        ForthWord* word = body[ndx].word;
        thread.setIndex(ndx + 1);
        trace(thread, word);
        word->execute(thread);
/*    } else {
        thread.popFrame();
	    thread.setTraceDepth(thread.getTraceDepth() - 1);
    } */
}

#else

class CompositeForthWordProxy : public CompositeForthWord {
public:
    CompositeForthWordProxy(CompositeForthWord& parent);
    virtual void execute(ForthThread& thread);
    virtual int getDisassemblyParamCount() const;

protected:
	virtual std::string getName() const;
    virtual std::string doDisassembly(const ForthThread& thread) const;

private:
    CompositeForthWord& parent;
};

CompositeForthWordProxy::CompositeForthWordProxy(CompositeForthWord& parentIn)
: CompositeForthWord(parentIn.name), parent(parentIn)
{
}

void CompositeForthWordProxy::execute(ForthThread& thread) {
    int ndx = thread.getIndex();
    if (ndx < body.size()) {
        ForthWord* word = parent.body[ndx].word;
        thread.setIndex(ndx + 1);
        trace(thread);
        word->execute(thread);
    } else {
        thread.popFrame();
	    thread.setTraceDepth(thread.getTraceDepth() - 1);
    }
}

std::string CompositeForthWordProxy::getName() const {
	return parent.getName();
}

std::string CompositeForthWordProxy::doDisassembly(const ForthThread& thread) const {
    return parent.doDisassembly(thread);
}

int CompositeForthWordProxy::getDisassemblyParamCount() const {
    return parent.getDisassemblyParamCount();
}

vvoid CompositeForthWord::execute(ForthThread& thread) {
    // first time called, so make a new stack frame
    CompositeForthWordProxy proxy = CompositeForthWordProxy(*this);
    thread.pushFrame(proxy);
    thread.setTraceDepth(thread.getTraceDepth() + 1);
    proxy.execute(thread);
}

#endif

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

