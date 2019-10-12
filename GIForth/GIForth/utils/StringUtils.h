#ifndef GIFORTH_STRINGUTILS_H
#define GIFORTH_STRINGUTILS_H

#include <string>

class StringUtils {
public:
	static void tabTo(std::string& line, int tabPos);
	static void rightTabTo(std::string& line, std::string addition, int tabPos);
	static void toLower(std::string& data);
};


#endif //GIFORTH_STRINGUTILS_H
