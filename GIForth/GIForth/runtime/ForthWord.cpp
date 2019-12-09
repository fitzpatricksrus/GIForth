//
// Created by Dad on 9/16/19.
//

#include "ForthWord.h"
#include "ForthThread.h"
#include "utils/StringUtils.h"

std::string ForthWord::getNameInVocabulary() const {
	std::string name(getDisassemblyName());
	size_t pos = name.find("::");
	if (pos == std::string::npos) {
		return name;
	} else {
		return name.substr(pos+2);
	}
}
