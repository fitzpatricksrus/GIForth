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

std::string NativeOSFunctions::inputBuffer;     // initializes to empty string
int NativeOSFunctions::inputPos = 0;

char NativeOSFunctions::peekNextChar() {
    if (inputPos >= inputBuffer.size()) {
        return '\0';
    } else {
        //TODO filter whitespace and convert it to spaces
        return inputBuffer[inputPos];
    }
}

char NativeOSFunctions::nextChar() {
    if (inputPos > inputBuffer.size()) {
        do {
            std::getline(std::cin, inputBuffer);
        } while (inputBuffer.empty());
        inputPos = 1;
        return inputBuffer[0];
    } else if (inputPos == inputBuffer.size()) {
        inputPos++;
        return '\0';
    } else {
        return inputBuffer[inputPos++];
    }
}

void NativeOSFunctions::printChar(char c) {
    std::cout << c;
}

void NativeOSFunctions::printString(const char *string) {
    std::cout << string;
}