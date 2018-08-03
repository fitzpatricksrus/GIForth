//
//  FMemory.hpp
//  GIForth
//
//  Created by Dad on 8/2/18.
//  Copyright © 2018 Dad. All rights reserved.
//

#ifndef FMemory_hpp
#define FMemory_hpp

#include "ForthMemory.hpp"

class FMemory : public ForthMemory {
public:
	FMemory(int memory, int scratch, int data, int retrn);
	virtual ~FMemory();
	virtual int getWord(int location) const;
	virtual void setWord(int location, int value);
	virtual char getByte(int location) const;
	virtual void setByte(int location, char value);
	virtual void* getPointer(int location) const;

	virtual int allocateMemory(int size);
	virtual void freeMemory(int location);

	virtual int peekDataStack(int ndx) const;
	virtual void rollDataStack(int ndx);
	virtual int popDataStack();
	virtual void pushDataStack(int value);
	
	virtual int fromReturnStack();
	virtual void toReturnStack(int value);
	virtual int returnStackDepth() const;
	
private:
	char* wordMemory;
	int firstFreeByte;
	int* dataStack;
	int dsp;
	int* returnStack;
	int rsp;
};

#endif /* FMemory_hpp */
