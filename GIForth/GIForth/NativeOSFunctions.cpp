//
//  NativeOSFunctions.cpp
//  GIForth
//
//  Created by Dad on 8/5/18.
//  Copyright © 2018 Dad. All rights reserved.
//

#include "NativeOSFunctions.hpp"
#include <string>
#include <iostream>
#include <algorithm>

int NativeOSFunctions::readALine(char* buffer, int maxLength) {
	std::string s;
	std::getline(std::cin, s);
	int sLen = (int)s.length();
	int size = std::min(maxLength, sLen);
	strncpy(buffer, s.c_str(), size);
	return size;
}

void NativeOSFunctions::printChar(char c) {
	std::cout << c;
}
