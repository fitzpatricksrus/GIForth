//
//  FMemory.cpp
//  GIForth
//
//  Created by Dad on 8/2/18.
//  Copyright © 2018 Dad. All rights reserved.
//

#include "FMemory.hpp"

#define intPtr(x) ((int*)x)

FMemory::FMemory(int memory, int data, int retrn)
: wordMemory(memory), firstFreeByte(0), dataStack(data), dsp(0), returnStack(retrn), rsp(0)
{
}

FMemory::~FMemory() {
}

int FMemory::getWord(int location) const {
	return *intPtr(&wordMemory[location]);
}

void FMemory::setWord(int location, int value) {
	*intPtr(&wordMemory[location]) = value;
}

char FMemory::getByte(int location) const {
	return wordMemory[location];
}

void FMemory::setByte(int location, char value) {
	wordMemory[location] = value;
}

void* FMemory::getPointer(int location) const {
	return (void*)(&wordMemory[location]);
}

int FMemory::allocateMemory(int size) {
	int result = firstFreeByte;
		//allocate word-sized chunks of memory
	size = (size + ForthMemory::CELL_SIZE - 1) / ForthMemory::CELL_SIZE * ForthMemory::CELL_SIZE;
	firstFreeByte = firstFreeByte + size;
	return result;
}

void FMemory::freeMemory(int location) {
	firstFreeByte = location - ForthMemory::CELL_SIZE;
}

int FMemory::peekDataStack(int ndx) const {
	return dataStack[dsp+ndx];
}

void FMemory::pokeDataStack(int ndx, int value) {
	dataStack[dsp+ndx] = value;
}

void FMemory::rollDataStack(int count) {
	int a0 = dataStack[dsp];
	for (int i = dsp; i > dsp - count; i++) {
		dataStack[i] = dataStack[i+1];
	}
	dataStack[dsp - count] = a0;
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
