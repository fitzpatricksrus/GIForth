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

static std::string inputBuffer = "";
static int inputPos = 0;

void NativeOSFunctions::printChar(char c) {
	std::cout << c;
}

char NativeOSFunctions::peekNextChar() {
    if (inputPos >= inputBuffer.size()) {
        while (inputPos >= inputBuffer.size()) {
            std::getline(std::cin, inputBuffer);
        }
        inputPos = 0;
        return ' '; // lines are separated by a space
    } else {
        //TODO filter whitespace and convert it to spaces
        return inputBuffer[inputPos];
    }
}

char NativeOSFunctions::nextChar() {
    char result = peekNextChar();
    inputPos++;
    return result;
}