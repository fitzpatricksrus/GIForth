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
#include <istream>
#include <cstring>

int NativeOSFunctions::accept(char* buffer, int size) {
    std::string buff;
    std::getline(currentInputStream(), buff);
    while (buff.size() > size) {
        std::cout << "WARNING: Input exceeded maximum length of " << std::to_string(size) << " characters.  Ignored." << std::endl;
        std::getline(std::cin, buff);
    }
    std::strcpy(buffer, buff.c_str());
    return buff.size();
}


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
			currentOutputStream() << "  ok " << std::endl;
			currentOutputStream().flush();
			if (!std::getline(currentInputStream(), inputBuffer)) {
				flushInput();
				popInputStream();
			}
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

void NativeOSFunctions::pushInputStream(std::istream &input) {
	inputStreams.push(&input);
}

void NativeOSFunctions::popInputStream(std::istream &input) {
	// pop only if the current stream is the stream passed in.
	if ((!inputStreams.empty()) && (inputStreams.top() == &input)) {
		inputStreams.pop();
	}
}

void NativeOSFunctions::popInputStream() {
	if (!inputStreams.empty()) {
		inputStreams.pop();
	}
}

std::istream& NativeOSFunctions::currentInputStream() {
	if (inputStreams.empty()) {
		return std::cin;
	} else {
		return *(inputStreams.top());
	}
}

void NativeOSFunctions::printChar(char c) {
	currentOutputStream() << c;
}

void NativeOSFunctions::printString(const char *string) {
	currentOutputStream() << string;
}

void NativeOSFunctions::printString(const std::string& string) {
	currentOutputStream() << string;
}

void NativeOSFunctions::endLine() {
	currentOutputStream() << std::endl;
}

void NativeOSFunctions::pushOutputStream(std::ostream &output) {
	outputStreams.push(&output);
}

void NativeOSFunctions::popOutputStream(std::ostream &output) {
	if ((!outputStreams.empty()) && (outputStreams.top() == &output)) {
		outputStreams.pop();
 	}
}

void NativeOSFunctions::popOutputStream() {
	outputStreams.pop();
}

std::ostream& NativeOSFunctions::currentOutputStream() {
	if (outputStreams.empty()) {
		return std::cout;
	} else {
		return *(outputStreams.top());
	}
}

std::stack<std::istream*> NativeOSFunctions::inputStreams;
std::stack<std::ostream*> NativeOSFunctions::outputStreams;

/*
 ACCEPT( addr u1 — u2 )
 Receives u1 characters (or until carriage return) from the terminal keyboard
 and stores them, starting at the address. The count of received characters is returned.

 WORD( char — addr )
 Parses one word from the input stream, using the character (usually blank) as a delimiter.
 Moves the string to the address HERE with the count in the first byte, leaving the address
 on the stack.
 */