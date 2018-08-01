//
//  Interpreter.hpp
//  GIForth
//
//  Created by Dad on 7/31/18.
//  Copyright © 2018 Dad. All rights reserved.
//

#ifndef Interpreter_hpp
#define Interpreter_hpp

#include "ForthInterpreter.hpp"
#include "ForthArchitecture.hpp"

class Interpreter : public ForthInterpreter {
public:
	Interpreter(ForthArchitecture& architecture);
	virtual void interpret();

private:
	ForthArchitecture& arch;
};

#endif /* Interpreter_hpp */
