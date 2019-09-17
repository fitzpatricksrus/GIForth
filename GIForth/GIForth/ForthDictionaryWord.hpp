//
//  ForthWord.hpp
//  GIForth
//
//  Created by Dad on 8/1/18.
//  Copyright © 2018 Dad. All rights reserved.
//
/*
#ifndef ForthWord_hpp
#define ForthWord_hpp

#include "runtime/ForthInstruction.hpp"

struct ForthDictionaryWord {
	enum MODE {
		PRIMITIVE,
		COMPILE_ONLY,
		IMMEDIATE,
		NORMAL
	};
	
	// null terminated string name here
	int nameIndex;
	int previousWordIndex;
	MODE mode;
};

#endif /* ForthWord_hpp */
