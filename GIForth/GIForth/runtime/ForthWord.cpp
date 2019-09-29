//
// Created by Dad on 9/16/19.
//

#include "ForthWord.h"
#include "ForthThread.h"
#include "utils/StringUtils.h"


static constexpr int INDENT = 4;

std::string ForthWord::getDisassembly(const ForthThread& thread) const {
    std::string line("[") ;
    StringUtils::rightTabTo(line, std::to_string(thread.getIndex() - 1), INDENT);
    line += " ] ";
    line += doDisassembly(thread);
    return line;
}

/*
int ForthWord::disassemblyParamCount() const {
    return 0;
}
*/
