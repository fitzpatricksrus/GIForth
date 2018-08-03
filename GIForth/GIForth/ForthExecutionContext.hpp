//
//  ForthExecutionContext.hpp
//  GIForth
//
//  Created by Dad on 7/31/18.
//  Copyright © 2018 Dad. All rights reserved.
//

#ifndef ForthExecutionContext_hpp
#define ForthExecutionContext_hpp

class ForthExecutionContext {
public:
	virtual ~ForthExecutionContext();
	virtual int getIP() const = 0;
		//IP = newIP
	virtual void setIP(int newIP) = 0;
		//IP += offset
	virtual void bumpIP(int offset) = 0;
		//return the current instruction and advance the IP
	virtual int getNextInstruction() = 0;
	
		//return the next character of console input
	virtual char peekInputChar() const = 0;
		//consume and return next character of console input
	virtual char nextInputChar() = 0;
		//print character to console
	virtual void printChar(char c) const = 0;
};

#endif /* ForthExecutionContext_hpp */
