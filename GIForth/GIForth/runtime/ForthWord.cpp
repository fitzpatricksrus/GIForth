//
// Created by Dad on 9/16/19.
//

#include "ForthWord.h"
#include "ForthThread.h"
#include <utils/NativeOSFunctions.hpp>


static constexpr int INDENT = 2;
static const std::string SPACES = "                                        ";

std::string ForthWord::getDisassembly(const ForthThread& thread) const {
    int depth = thread.returnStackDepth();
    std::string line = SPACES.substr(0, depth * INDENT);
    std::string ndx = std::to_string(thread.getIndex() - 1);
    if (ndx.size() < 2) {
        ndx = SPACES.substr(0, 2 - ndx.size()) + ndx;
    }
    std::string dis = doDisassembly(thread);
    line.append("[").append(ndx).append("] ").append(dis);
    return line;
}

/*
int ForthWord::disassemblyParamCount() const {
    return 0;
}
*/
