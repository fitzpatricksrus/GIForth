//
// Created by Dad on 9/29/19.
//

#include "StringUtils.h"

static const std::string SPACES = "                                                                                                                        ";

void StringUtils::tabTo(std::string& line, int tabPos) {
	if (line.length() < tabPos) {
		line += SPACES.substr(0, tabPos - line.length() - 1);
	} else {
		line += " ";
	}
}

void StringUtils::rightTabTo(std::string& line, std::string addition, int tabPos) {
	int contentLength = line.length() + addition.length();
	if (contentLength < tabPos) {
		line += SPACES.substr(0, tabPos - contentLength);
	} else {
		line += " ";
	};
	line += addition;
}

#include <algorithm>
#include <cctype>
#include <string>

void StringUtils::toLower(std::string& data) {
	std::transform(data.begin(), data.end(), data.begin(),
				   [](unsigned char c) { return std::tolower(c); });
}
