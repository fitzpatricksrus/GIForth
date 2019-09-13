//
//  ExecutionContext.cpp
//  GIForth
//
//  Created by Dad on 8/3/18.
//  Copyright © 2018 Dad. All rights reserved.
//

#include "ExecutionContext.hpp"

#include "ForthMemory.hpp"
#include "NativeOSFunctions.hpp"

ExecutionContext::ExecutionContext(ForthMemory& memoryIn)
: ip(0), memory(memoryIn), inputLine(), inputLength(0), inputPosition(1) {
    // the inputPosition of 1 will force a refill of the input buffer the
    // first time it is used.  See peekInputChar
}

ExecutionContext::~ExecutionContext() {
}

int ExecutionContext::getIP() const {
	return ip;
}

void ExecutionContext::setIP(int newIP) {
	ip = newIP;
}

void ExecutionContext::bumpIP(int offset) {
	ip += offset;
}

int ExecutionContext::getNextInstruction() {
	int result = memory.getWord(ip);
	ip += ForthMemory::CELL_SIZE;
	return result;
}

char ExecutionContext::peekInputChar() const {
    // NOTE: changing this comparison requires changes to the constructor
	while (inputPosition > inputLength) {
	    // the const case here is because the input buffer storage is invisible
	    // to the caller.
        const_cast<ExecutionContext*>(this)->readAnotherInputLine();
	}
	return inputLine[inputPosition];
}

void ExecutionContext::readAnotherInputLine() {
    inputPosition = 0;
    inputLength = NativeOSFunctions::readALine(inputLine.data(), MAX_INPUT_LENGTH);
    inputLine[inputLength] = ' ';
}

char ExecutionContext::nextInputChar() {
	char result = peekInputChar();
	inputPosition++;
	return result;
}

void ExecutionContext::printChar(char c) const {
	NativeOSFunctions::printChar(c);
}

void ExecutionContext::flushInput() {
	inputPosition = inputLength;
}


