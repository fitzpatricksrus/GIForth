//
//  FMemory.cpp
//  GIForth
//
//  Created by Dad on 8/2/18.
//  Copyright © 2018 Dad. All rights reserved.
//

#include "FMemory.hpp"

#define intPtr(x) ((int*)x)

int FMemory::getWord(int location) const {
	return *intPtr(wordMemory + location*sizeof(int));
}

void FMemory::setWord(int location, int value) {
	*intPtr(wordMemory + location*sizeof(int)) = value;
}

char FMemory::getByte(int location) const {
	return wordMemory[location];
}

void FMemory::setByte(int location, char value) {
	wordMemory[location] = value;
}

void* FMemory::getPointer(int location) const {
	return wordMemory + location;
}

int FMemory::allocateMemory(int size) {
	int result = firstFreeByte;
		//allocate word-sized chunks of memory
	size = (size + sizeof(int) - 1) / sizeof(int) * sizeof(int);
	firstFreeByte = firstFreeByte + size;
	return result;
}

void FMemory::freeMemory(int location) {
	firstFreeByte = location - sizeof(int);
}

int FMemory::peekDataStack(int ndx) const {
	return dataStack[dsp+ndx];
}

void FMemory::rollDataStack(int ndx) {
	int a0 = dataStack[dsp];
	for (int i = dsp; i > dsp - ndx; i++) {
		dataStack[i] = dataStack[i+1];
	}
	dataStack[dsp - ndx] = a0;
}

int FMemory::popDataStack() {
	return dataStack[--dsp];
}

void FMemory::pushDataStack(int value) {
	dataStack[dsp++] = value;
}

int FMemory::fromReturnStack() {
	return returnStack[--rsp];
}

void FMemory::toReturnStack(int value) {
	returnStack[rsp++] = value;
}

int FMemory::returnStackDepth() const {
	return rsp;
}
