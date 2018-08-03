//
//  ForthDictionary.hpp
//  GIForth
//
//  Created by Dad on 8/2/18.
//  Copyright © 2018 Dad. All rights reserved.
//

#ifndef ForthDictionary_hpp
#define ForthDictionary_hpp

#include "ForthMemory.hpp"
#include "ForthWord.hpp"

struct ForthDictionary : public ForthWord {
	static int create(ForthMemory* memory, char* name);
	
	static int getTopWord();
	static int findWord(ForthMemory* memory, char* name);
	
	static void beingCompile(ForthMemory* memory, char* name, ForthWord::MODE mode);
	static void compileWord(ForthMemory* memory, int value);
	static int endCompile(ForthMemory* memory);
	static void abortCompile(ForthMemory* memory);

private:
	int topWord;
};

#endif /* ForthDictionary_hpp */
