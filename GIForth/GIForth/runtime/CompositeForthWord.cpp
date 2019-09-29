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

void CompositeForthWord::execute(ForthThread& thread) {
	static const std::string SPACES = "                                                                                                                        ";
	static constexpr int TAB_POSITION = 60;
	
	if (thread.getCurrentWord() != this) {
        // first time called, so make a new stack frame
        thread.pushFrame(this);
    }
    int ndx = thread.getIndex();
    if (ndx < body.size()) {
        ForthWord* word = body[ndx].word;
        thread.setIndex(ndx + 1);
        if (isTraceEnabled()) {
        	std::string line;
	        line += "( ";
	        line += shortStackDump(thread);
	        line += " )";
	        if (line.length() < TAB_POSITION) {
		        line += SPACES.substr(0, TAB_POSITION - line.length());
	        } else {
		        line += " ";
	        }
	        line += word->getDisassembly(thread);
	        NativeOSFunctions::printString(line);
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

std::vector<std::string> CompositeForthWord::getDisassembly() const {
    std::vector<std::string> result(size());
    ForthThread disassemblyThread(const_cast<CompositeForthWord*>(this));
    while (!disassemblyThread.currentWordComplete()) {
        ForthCell cell = disassemblyThread.getNextCell();
        std::string line(cell.word->getDisassembly(disassemblyThread));
        result.push_back(line);
        disassemblyThread.offsetIndex(cell.word->getDisassemblyParamCount());
    }
    return result;
}

std::string CompositeForthWord::doDisassembly(const ForthThread& thread) const {
    return name;
}

int CompositeForthWord::getDisassemblyParamCount() const {
    return 0;
}

