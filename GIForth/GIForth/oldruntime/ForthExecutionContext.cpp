//
//  ForthForthExecutionContext.cpp
//  GIForth
//
//  Created by Dad on 7/31/18.
//  Copyright © 2018 Dad. All rights reserved.
//

/*


#include "runtime/ForthMemory.hpp"
#include "NativeOSFunctions.hpp"

ForthExecutionContext::ForthExecutionContext(ForthMemory& memoryIn)
        : ip(0), memory(memoryIn), inputLine(), inputLength(0), inputPosition(1) {
    // the inputPosition of 1 will force a refill of the input buffer the
    // first time it is used.  See peekInputChar
}

int ForthExecutionContext::getIP() const {
    return ip;
}

void ForthExecutionContext::setIP(int newIP) {
    ip = newIP;
}

void ForthExecutionContext::bumpIP(int offset) {
    ip += offset;
}

int ForthExecutionContext::getNextInstruction() {
    int result = memory.getWord(ip);
    ip += ForthMemory::WORD_SIZE;
    return result;
}

char ForthExecutionContext::peekInputChar() const {
    // NOTE: changing this comparison requires changes to the constructor
    while (inputPosition > inputLength) {
        // the const case here is because the input buffer storage is invisible
        // to the caller.
        const_cast<ForthExecutionContext*>(this)->readAnotherInputLine();
    }
    return inputLine[inputPosition];
}

void ForthExecutionContext::readAnotherInputLine() {
    inputPosition = 0;
    inputLength = NativeOSFunctions::readALine(inputLine.data(), MAX_INPUT_LENGTH);
    inputLine[inputLength] = ' ';
}

char ForthExecutionContext::nextInputChar() {
    char result = peekInputChar();
    inputPosition++;
    return result;
}

void ForthExecutionContext::printChar(char c) const {
    NativeOSFunctions::printChar(c);
}

void ForthExecutionContext::flushInput() {
    inputPosition = inputLength;
}

 */