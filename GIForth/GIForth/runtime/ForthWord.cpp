//
// Created by Dad on 9/16/19.
//

#include "ForthWord.h"
#include "ForthThread.h"
#include "utils/StringUtils.h"


static constexpr int INDENT = 4;

std::string ForthWord::getTrace(const ForthThread& thread) const {
    std::string line("[") ;
    StringUtils::rightTabTo(line, std::to_string(thread.getIndex() - 1), INDENT);
    line += " ] ";
    line += getDisassemblyDetail(thread);
    return line;
}

std::string ForthWord::getName() const {
	std::string name(getDisassemblyName());
	size_t pos = name.find("::");
	if (pos == std::string::npos) {
		return name;
	} else {
		return name.substr(pos);
	}
}

/*
int ForthWord::disassemblyParamCount() const {
    return 0;
}
*/
