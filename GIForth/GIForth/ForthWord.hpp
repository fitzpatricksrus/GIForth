//
//  ForthWord.hpp
//  GIForth
//
//  Created by Dad on 8/1/18.
//  Copyright © 2018 Dad. All rights reserved.
//

#ifndef ForthWord_hpp
#define ForthWord_hpp

#include <stdio.h>
#include "ForthInstruction.hpp"

class ForthWord {
public:
	enum MODE {
		PRIMITIVE,
		COMPILE_ONLY,
		IMMEDIATE,
		NORMAL
	};
	
	// null terminated string
	char* name;
	ForthWord* previous;
	MODE mode;
	ForthInstruction words[];

};

#endif /* ForthWord_hpp */
