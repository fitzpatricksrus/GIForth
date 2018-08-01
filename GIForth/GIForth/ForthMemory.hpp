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
	virtual int getWord(int location) = 0;
	virtual void setWord(int location, int value) = 0;
	virtual char getByte(int location) = 0;
	virtual void setByte(int location, char value) = 0;
	
	virtual int peekDataStack(int ndx) = 0;
	virtual int popDataStack() = 0;
	virtual void pushDataStack(int value) = 0;
	
	virtual int popReturnStack() = 0;
	virtual void pushReturnStack(int value) = 0;
	virtual int returnStackDepth() = 0;
};

#endif /* ForthMemory_hpp */
