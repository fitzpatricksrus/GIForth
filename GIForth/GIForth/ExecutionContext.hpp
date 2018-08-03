//
//  ExecutionContext.hpp
//  GIForth
//
//  Created by Dad on 8/3/18.
//  Copyright © 2018 Dad. All rights reserved.
//

#ifndef ExecutionContext_hpp
#define ExecutionContext_hpp

#include "ForthExecutionContext.hpp"

class ForthMemory;

class ExecutionContext : public ForthExecutionContext {
public:
	ExecutionContext(ForthMemory* memory);
	virtual ~ExecutionContext();

	virtual int getIP() const;
		//IP = newIP
	virtual void setIP(int newIP);
		//IP += offset
	virtual void bumpIP(int offset);
		//return the current instruction and advance the IP
	virtual int getNextInstruction();
	
		//return the next character of console input
	virtual char peekInputChar() const;
		//consume and return next character of console input
	virtual char nextInputChar();
		//print character to console
	virtual void printChar(char c) const;
	
private:
	int ip;
	ForthMemory* memory;
};



#endif /* ExecutionContext_hpp */
