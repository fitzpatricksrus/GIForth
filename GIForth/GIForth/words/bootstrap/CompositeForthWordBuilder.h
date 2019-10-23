//
// Created by Dad on 9/28/19.
//

#ifndef GIFORTH_COMPOSITEFORTHWORDBUILDER_H
#define GIFORTH_COMPOSITEFORTHWORDBUILDER_H

#include <stack>
#include "runtime/CompositeForthWord.h"

class CompositeForthWordBuilder {
public:
	CompositeForthWordBuilder(const std::string& name);
	CompositeForthWordBuilder& operator+=(const ForthCell& cell);
	CompositeForthWordBuilder& compileCell(const ForthCell& cell);
	CompositeForthWordBuilder& compileConstant(const ForthCell& cell);
	CompositeForthWordBuilder& compileIf();
	CompositeForthWordBuilder& compileElse();
	CompositeForthWordBuilder& compileEndIf();
	CompositeForthWordBuilder& compileWhile();
	CompositeForthWordBuilder& compileDo();
    CompositeForthWordBuilder& compileEndWhile();
    CompositeForthWordBuilder& compileRepeat();
    CompositeForthWordBuilder& compileForever();

	
	CompositeForthWord build();
	
private:
	CompositeForthWord word;
	std::stack<int> ifStack;
};

#endif //GIFORTH_COMPOSITEFORTHWORDBUILDER_H
