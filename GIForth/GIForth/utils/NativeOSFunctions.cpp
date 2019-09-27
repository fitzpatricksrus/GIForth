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
			std::cout << "> ";
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

void NativeOSFunctions::flushInput() {
	inputBuffer = "";
	inputPos = 0;
}


void NativeOSFunctions::printChar(char c) {
    std::cout << c;
}

void NativeOSFunctions::printString(const char *string) {
    std::cout << string;
}

void NativeOSFunctions::printString(const std::string& string) {
    std::cout << string;
}

/*
 ACCEPT( addr u1 — u2 )
 Receives u1 characters (or until carriage return) from the terminal keyboard
 and stores them, starting at the address. The count of received characters is returned.

 WORD( char — addr )
 Parses one word from the input stream, using the character (usually blank) as a delimiter.
 Moves the string to the address HERE with the count in the first byte, leaving the address
 on the stack.
 */