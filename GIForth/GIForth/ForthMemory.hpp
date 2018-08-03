//
//  ForthMemory.hpp
//  GIForth
//
//  Created by Dad on 7/31/18.
//  Copyright © 2018 Dad. All rights reserved.
//

#ifndef ForthMemory_hpp
#define ForthMemory_hpp

class ForthMemory {
public:
	virtual ~ForthMemory();
		// get the cell at the specified location
	virtual int getWord(int location) = 0;
		// set contents of cell at specified location
	virtual void setWord(int location, int value) = 0;
		// get bytfe at specified location
	virtual char getByte(int location) = 0;
		// set byte at specified location
	virtual void setByte(int location, char value) = 0;
		// return the C address of the specified location in actual memory.
		// this routine is for internal use only for efficiently doing
		// overlays of C structures onto the VM memory.
	virtual void* getPointer(int location) = 0;

		// allocated a chunk of VM memory
	virtual int allocateMemory(int size) = 0;
		// free a chunk of VM memory
	virtual void freeMemory(int location) = 0;
	
	virtual int peekDataStack(int ndx) = 0;
	virtual void rollDataStack(int ndx) = 0;
	virtual int popDataStack() = 0;
	virtual void pushDataStack(int value) = 0;
	
	virtual int fromReturnStack() = 0;
	virtual void toReturnStack(int value) = 0;
	virtual int returnStackDepth() = 0;
};

#endif /* ForthMemory_hpp */
