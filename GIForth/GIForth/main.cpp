//
//  main.cpp
//  GIForth
//
//  Created by Dad on 7/31/18.
//  Copyright © 2018 Dad. All rights reserved.
//

#include <iostream>

class ForthMemory {
public:
	virtual int getWord(int location) = 0;
	virtual void setWord(int location, int value) = 0;
	virtual char getByte(int location) = 0;
	virtual void setByte(int location, char value) = 0;
	
	virtual int peekDataStack(int ndx) = 0;
	virtual int popDataStack() = 0;
	virtual void pushDataStack() = 0;
	
	virtual int popReturnStack() = 0;
	virtual void pushReturnStack(int value) = 0;
};

class ForthExecutionContext {
public:
	virtual int getIP() = 0;
	virtual void setIP(int newIP) = 0;
	virtual void bumpIP(int offset) = 0;
	virtual int getNextInstruction() = 0;
};

class Architecture : public ForthMemory, public ForthExecutionContext {

};


int main(int argc, const char * argv[]) {
	// insert code here...
	std::cout << "Hello, World!\n";
	return 0;
}
