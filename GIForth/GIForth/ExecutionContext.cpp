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

static const int MAX_INPUT_LENGTH = 255;

ExecutionContext::ExecutionContext(ForthMemory* memoryIn)
: ip(0), memory(memoryIn), inputLine(nullptr), inputLength(0), inputPosition(0) {
	inputLine = new char[MAX_INPUT_LENGTH+1];
}

ExecutionContext::~ExecutionContext() {
	delete[] inputLine;
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
	int result = memory->getWord(ip);
	ip += ForthMemory::CELL_SIZE;
	return result;
}

char ExecutionContext::peekInputChar() const {
	while (inputPosition == inputLength) {
		const_cast<int&>(inputLength) = NativeOSFunctions::readALine(inputLine, MAX_INPUT_LENGTH) + 1;
		// the +1 is so we include the terminating 0 as input.
	}
	return inputLine[inputPosition];
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


