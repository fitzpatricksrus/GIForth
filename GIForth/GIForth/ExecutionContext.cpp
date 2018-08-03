//
//  ExecutionContext.cpp
//  GIForth
//
//  Created by Dad on 8/3/18.
//  Copyright © 2018 Dad. All rights reserved.
//

#include "ExecutionContext.hpp"

#include "ForthMemory.hpp"

ExecutionContext::ExecutionContext(ForthMemory* memoryIn)
: ip(0), memory(memoryIn) {
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
	int result = memory->getWord(ip);
	ip += ForthMemory::CELL_SIZE;
	return result;
}

char ExecutionContext::peekInputChar() const {
	
}

char ExecutionContext::nextInputChar() {

}

void ExecutionContext::printChar(char c) const {

}
