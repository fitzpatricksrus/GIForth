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
	virtual int getIP() = 0;
	virtual void setIP(int newIP) = 0;
	virtual void bumpIP(int offset) = 0;
	virtual int getNextInstruction() = 0;
};

#endif /* ForthExecutionContext_hpp */
