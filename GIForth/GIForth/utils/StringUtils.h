//
// Created by Dad on 9/29/19.
//

#ifndef GIFORTH_STRINGUTILS_H
#define GIFORTH_STRINGUTILS_H

#include <string>

class StringUtils {
public:
	static void tabTo(std::string& line, int tabPos);
	static void rightTabTo(std::string& line, std::string addition, int tabPos);
};


#endif //GIFORTH_STRINGUTILS_H
