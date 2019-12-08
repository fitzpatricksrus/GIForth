//
// Created by Dad on 9/28/19.
//

#ifndef GIFORTH_COMPOSITEFORTHWORDBUILDER_H
#define GIFORTH_COMPOSITEFORTHWORDBUILDER_H

#include <stack>
#include "runtime/CompositeForthWord.h"

/*
 <bool> if ... endif
 <bool> if ... else ... endif
 while <bool> do ... endWhile
 repeat ... forever
 repeat ... <bool> until
 */

class CompositeForthWordBuilder {
public:
	CompositeForthWordBuilder(const std::string& name);
	CompositeForthWordBuilder& operator+=(const ForthCell& cell);
	CompositeForthWordBuilder& compileCell(const ForthCell& cell);
	CompositeForthWordBuilder& compileConstant(const ForthCell& cell);
	CompositeForthWordBuilder& compileWord(const ForthCell::WORD_TYPE wordIn);
	CompositeForthWordBuilder& compileInt(const ForthCell::INT_TYPE intIn);
	CompositeForthWordBuilder& compilePtr(const ForthCell::PTR_TYPE ptrIn);
	CompositeForthWordBuilder& compileIf();
	CompositeForthWordBuilder& compileElse();
	CompositeForthWordBuilder& compileEndIf();
	CompositeForthWordBuilder& compileWhile();
	CompositeForthWordBuilder& compileDo();
    CompositeForthWordBuilder& compileEndWhile();
    CompositeForthWordBuilder& compileRepeat();
	CompositeForthWordBuilder& compileForever();
	CompositeForthWordBuilder& compileUntil();

	CompositeForthWordBuilder& forwardMark();			// if
	CompositeForthWordBuilder& forwardResolve();		// endif
	CompositeForthWordBuilder& forwardMarkResolve();	// else
	CompositeForthWordBuilder& backwardMark();			// repeat
	CompositeForthWordBuilder& backwardResolve();		// until/forever

	CompositeForthWord build();
	
private:
	std::string name;
	std::vector<ForthCell> word;
	std::stack<int> ifStack;
};

#endif //GIFORTH_COMPOSITEFORTHWORDBUILDER_H
